#include "mlpch.h"
#include "Renderer2D.h"

#include "Framebuffer.h"

#include <Merlin/Core/ResourceManager.h>
#include <Merlin/Core/Scene/Camera.h>

#include <glad.h>

#include <ft2build.h>
#include FT_FREETYPE_H

namespace Merlin::Renderer
{
	Framebuffer* Renderer2D::Framebuffer;

	static const size_t MaxQuadCount = 1000;
	static const size_t MaxVertexCount = MaxQuadCount * 4;
	static const size_t MaxIndexCount = MaxQuadCount * 6;
	static const size_t MaxTextures = 32;

	struct Vertex
	{
		Vertex() {}

		Vertex(Vector3 pos, Vector4 col, Vector2 coords, float texID)
		{
			this->Position = pos;
			this->Color = col;
			this->TexCoords = coords;
			this->TexID = texID;
		}

		Vector3 Position;
		Vector4 Color;
		Vector2 TexCoords;
		float TexID = 0;
	};

	struct RenderData
	{
		GLuint VAO = 0;
		GLuint VBO = 0;
		GLuint IBO = 0;

		Vertex* QuadBuffer = nullptr;
		Vertex* QuadBufferPtr = nullptr;
		std::map<Ref<Material>, std::vector<Vertex*>> VertexData;

		uint32_t IndexCount = 0;

		std::array<uint32_t, MaxTextures> TextureSlots;
		uint32_t TextureSlotIndex = 1;
		uint32_t WhiteTexture = 0;
	};

	struct Character
	{
		uint32_t TextureID = 0;
		Vector2 Size;
		Vector2 Bearing;
		uint32_t Advance = 0;
	};

	static std::unordered_map<GLchar, Character> Characters;
	static RenderData s_Data;

	void Renderer2D::OnAwake()
	{
		// Quad Renderer

		s_Data.QuadBuffer = new Vertex[MaxVertexCount];

		glGenVertexArrays(1, &s_Data.VAO);
		glBindVertexArray(s_Data.VAO);

		glGenBuffers(1, &s_Data.VBO);
		glBindBuffer(GL_ARRAY_BUFFER, s_Data.VBO);
		glBufferData(GL_ARRAY_BUFFER, MaxVertexCount *  sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);

		glEnableVertexArrayAttrib(s_Data.VAO, 0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, Position));

		glEnableVertexArrayAttrib(s_Data.VAO, 1);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, Color));

		glEnableVertexArrayAttrib(s_Data.VAO, 2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, TexCoords));

		glEnableVertexArrayAttrib(s_Data.VAO, 3);
		glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, TexID));

		uint32_t indices[MaxIndexCount];
		uint32_t offset = 0;
		for (size_t i = 0; i < MaxIndexCount; i += 6)
		{
			indices[i + 0] = 0 + offset;
			indices[i + 1] = 1 + offset;
			indices[i + 2] = 2 + offset;

			indices[i + 3] = 2 + offset;
			indices[i + 4] = 3 + offset;
			indices[i + 5] = 0 + offset;

			offset += 4;
		}

		glGenBuffers(1, &s_Data.IBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, s_Data.IBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		// Setup default texture
		glCreateTextures(GL_TEXTURE_2D, 1, &s_Data.WhiteTexture);
		glBindTexture(GL_TEXTURE_2D, s_Data.WhiteTexture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		uint32_t color = 0xffffffff;
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, &color);

		s_Data.TextureSlots[0] = s_Data.WhiteTexture;
		for (size_t i = 1; i < MaxTextures; i++)
			s_Data.TextureSlots[i] = 0;

		// FreeType Renderer

		FT_Library ft;

		if (FT_Init_FreeType(&ft))
		{
			DEBUG_LOG_ERROR("Error: FreeType could not init Library");
		}

		FT_Face face;
		if (FT_New_Face(ft, "..\\Sandbox\\Assets\\Fonts\\Times.TTF", 0, &face))
		{
			DEBUG_LOG_ERROR("Error: FreeType failed to load font");
		}
		else
		{
			FT_Set_Pixel_Sizes(face, 0, 48);
			glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

			for (unsigned char c = 0; c < 128; c++)
			{
				if (FT_Load_Char(face, c, 1L << 2))
				{
					DEBUG_LOG_ERROR("Error: FreeType Failed to load Glyph");
				}

				uint32_t texture;
				
				glGenTextures(1, &texture);
				glBindTexture(GL_TEXTURE_2D, texture);
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, face->glyph->bitmap.width, face->glyph->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer);

				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

				Character character =
				{
					texture,
					Vector2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
					Vector2(face->glyph->bitmap_left, face->glyph->bitmap_top),
					static_cast<uint32_t>(face->glyph->advance.x)
				};

				Characters.insert(std::pair<char, Character>(c, character));
			}

			glBindTexture(GL_TEXTURE_2D, 0);
		}

		FT_Done_Face(face);
		FT_Done_FreeType(ft);

		// Create Framebuffer
		FrameBufferSpecs fbSpec;
		fbSpec.Width = 1280;
		fbSpec.Height = 720;
		Framebuffer = new Renderer::Framebuffer(fbSpec);
	}

	void Renderer2D::OnDestroy()
	{
		glDeleteVertexArrays(1, &s_Data.VAO);
		glDeleteBuffers(1, &s_Data.VBO);
		glDeleteBuffers(1, &s_Data.IBO);

		delete[] s_Data.QuadBuffer;
	}
	void Renderer2D::BeginScene()
	{
		BeginBatch();
	}

	void Renderer2D::EndScene()
	{
		Framebuffer->Bind();
		for (auto& drawData : s_Data.VertexData)
		{
			glUseProgram(drawData.first->shader->ID);
			Camera::GetMain()->SetShaderMatrices(drawData.first->shader);

			for (int i = 0; i < drawData.second.size(); i += 4)
			{
				if (s_Data.IndexCount >= MaxIndexCount || s_Data.TextureSlotIndex > (MaxTextures - 1))
				{
					EndBatch();
					Flush();
					BeginBatch();
				}

				s_Data.QuadBufferPtr->Position = drawData.second[i]->Position;
				s_Data.QuadBufferPtr->Color = drawData.second[i]->Color;
				s_Data.QuadBufferPtr->TexCoords = drawData.second[i]->TexCoords;
				s_Data.QuadBufferPtr->TexID = drawData.second[i]->TexID;
				s_Data.QuadBufferPtr++;

				s_Data.QuadBufferPtr->Position = drawData.second[i + 1]->Position;
				s_Data.QuadBufferPtr->Color = drawData.second[i + 1]->Color;
				s_Data.QuadBufferPtr->TexCoords = drawData.second[i + 1]->TexCoords;
				s_Data.QuadBufferPtr->TexID = drawData.second[i + 1]->TexID;
				s_Data.QuadBufferPtr++;

				s_Data.QuadBufferPtr->Position = drawData.second[i + 2]->Position;
				s_Data.QuadBufferPtr->Color = drawData.second[i + 2]->Color;
				s_Data.QuadBufferPtr->TexCoords = drawData.second[i + 2]->TexCoords;
				s_Data.QuadBufferPtr->TexID = drawData.second[i + 2]->TexID;
				s_Data.QuadBufferPtr++;

				s_Data.QuadBufferPtr->Position = drawData.second[i + 3]->Position;
				s_Data.QuadBufferPtr->Color = drawData.second[i + 3]->Color;
				s_Data.QuadBufferPtr->TexCoords = drawData.second[i + 3]->TexCoords;
				s_Data.QuadBufferPtr->TexID = drawData.second[i + 3]->TexID;
				s_Data.QuadBufferPtr++;

				s_Data.IndexCount += 6;
			}

			EndBatch();
			Flush();
			BeginBatch();
		}

		s_Data.VertexData.clear();
		Framebuffer->Unbind();
	}

	void Renderer2D::BeginBatch()
	{
		s_Data.QuadBufferPtr = s_Data.QuadBuffer;
	}

	void Renderer2D::EndBatch()
	{
		GLsizeiptr size = (uint8_t*)s_Data.QuadBufferPtr - (uint8_t*)s_Data.QuadBuffer;
		glBindBuffer(GL_ARRAY_BUFFER, s_Data.VBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, size, s_Data.QuadBuffer);
	}

	void Renderer2D::Flush()
	{
		for (uint32_t i = 0; i < s_Data.TextureSlotIndex; i++)
			glBindTextureUnit(i, s_Data.TextureSlots[i]);

		glBindVertexArray(s_Data.VAO);
		glDrawElements(GL_TRIANGLES, s_Data.IndexCount, GL_UNSIGNED_INT, nullptr);

		s_Data.IndexCount = 0;
	}

	void Renderer2D::DrawQuad(Transform* transform, Ref<Material> material, Ref<Sprite> sprite, const Vector4& color)
	{
		float textureIndex = 0.0f;
		for (uint32_t i = 1; i < s_Data.TextureSlotIndex; i++)
		{
			if (s_Data.TextureSlots[i] == sprite->GetTexture()->ID)
			{
				textureIndex = (float)i;
				break;
			}
		}

		if (textureIndex == 0.0f)
		{
			textureIndex = (float)s_Data.TextureSlotIndex;
			s_Data.TextureSlots[s_Data.TextureSlotIndex] = sprite->GetTexture()->ID;
			s_Data.TextureSlotIndex++;
		}

		s_Data.VertexData[material].push_back(new Vertex(
			{ transform->position.x - transform->scale.x, transform->position.y - transform->scale.y, transform->position.z },
			color,
			sprite->GetTexCoords()[3],
			textureIndex
		));
		s_Data.VertexData[material].push_back(new Vertex(
			{ transform->position.x + transform->scale.x, transform->position.y - transform->scale.y, transform->position.z },
			color,
			sprite->GetTexCoords()[2],
			textureIndex
		));
		s_Data.VertexData[material].push_back(new Vertex(
			{ transform->position.x + transform->scale.x, transform->position.y + transform->scale.y, transform->position.z },
			color,
			sprite->GetTexCoords()[1],
			textureIndex
		));
		s_Data.VertexData[material].push_back(new Vertex(
			{ transform->position.x - transform->scale.x, transform->position.y + transform->scale.y, transform->position.z },
			color,
			sprite->GetTexCoords()[0],
			textureIndex
		));
	}

	void Renderer2D::DrawQuad(const Vector3& pos, const Vector2& size, const Vector4& color)
	{
		Ref<Material> standardMaterial = ResourceManager::GetMaterial("StandardMaterial");

		s_Data.VertexData[standardMaterial].push_back(new Vertex(
			{ pos.x - size.x, pos.y - size.y, pos.z },
			color,
			{ 0.0f, 0.0f },
			0.0f
		));
		s_Data.VertexData[standardMaterial].push_back(new Vertex(
			{ pos.x + size.x, pos.y - size.y, pos.z },
			color,
			{ 0.0f, 0.0f },
			0.0f
		));
		s_Data.VertexData[standardMaterial].push_back(new Vertex(
			{ pos.x + size.x, pos.y + size.y, pos.z },
			color,
			{ 0.0f, 0.0f },
			0.0f
		));
		s_Data.VertexData[standardMaterial].push_back(new Vertex(
			{ pos.x - size.x, pos.y + size.y, pos.z },
			color,
			{ 0.0f, 0.0f },
			0.0f
		));
	}

	void Renderer2D::DrawQuad(const Vector3& pos, const Vector2& size, Texture2D* texture)
	{
		Ref<Material> standardMaterial = ResourceManager::GetMaterial("StandardMaterial");

		const Vector4 color = { 1.0f, 1.0f, 1.0f, 1.0f };

		float textureIndex = 0.0f;
		for (uint32_t i = 1; i < s_Data.TextureSlotIndex; i++)
		{
			if (s_Data.TextureSlots[i] == texture->ID)
			{
				textureIndex = (float)i;
				break;
			}
		}

		if (textureIndex == 0.0f)
		{
			textureIndex = (float)s_Data.TextureSlotIndex;
			s_Data.TextureSlots[s_Data.TextureSlotIndex] = texture->ID;
			s_Data.TextureSlotIndex++;
		}

		s_Data.VertexData[standardMaterial].push_back(new Vertex(
			{ pos.x - size.x, pos.y - size.y, pos.z },
			color,
			{ 0.0f, 0.0f },
			textureIndex
		));
		s_Data.VertexData[standardMaterial].push_back(new Vertex(
			{ pos.x + size.x, pos.y - size.y, pos.z },
			color,
			{ 1.0f, 0.0f },
			0.0f
		));
		s_Data.VertexData[standardMaterial].push_back(new Vertex(
			{ pos.x + size.x, pos.y + size.y, pos.z },
			color,
			{ 1.0f, 1.0f },
			textureIndex
		));
		s_Data.VertexData[standardMaterial].push_back(new Vertex(
			{ pos.x - size.x, pos.y + size.y, pos.z },
			color,
			{ 0.0f, 1.0f },
			textureIndex
		));
	}

	void Renderer2D::DrawText(Vector3 pos, const Vector2& size, const std::string& text)
	{
		Ref<Material> fontMaterial = ResourceManager::GetMaterial("StandardFontMaterial");
		std::string::const_iterator c;

		for (c = text.begin(); c != text.end(); c++)
		{
			Character ch = Characters[*c];

			float textureIndex = 0.0f;
			for (uint32_t i = 1; i < s_Data.TextureSlotIndex; i++)
			{
				if (s_Data.TextureSlots[i] == ch.TextureID)
				{
					textureIndex = (float)i;
					break;
				}
			}

			if (textureIndex == 0.0f)
			{
				textureIndex = (float)s_Data.TextureSlotIndex;
				s_Data.TextureSlots[s_Data.TextureSlotIndex] = ch.TextureID;
				s_Data.TextureSlotIndex++;
			}

			float xpos = pos.x + ch.Bearing.x * size.x;
			float ypos = pos.y - (ch.Size.y - ch.Bearing.y) * size.y;

			float width = (ch.Size.x * size.x) * 0.5f;
			float height = (ch.Size.y * size.y) * 0.5f;

			s_Data.VertexData[fontMaterial].push_back(new Vertex(
				{ xpos - width, ypos - height, pos.z },
				{ 1.0f, 1.0f, 1.0f, 1.0f },
				{ 0.0f, 1.0f },
				textureIndex
			));
			s_Data.VertexData[fontMaterial].push_back(new Vertex(
				{ xpos + width, ypos - height, pos.z },
				{ 1.0f, 1.0f, 1.0f, 1.0f },
				{ 1.0f, 1.0f },
				textureIndex
			));
			s_Data.VertexData[fontMaterial].push_back(new Vertex(
				{ xpos + width, ypos + height, pos.z },
				{ 1.0f, 1.0f, 1.0f, 1.0f },
				{ 1.0f, 0.0f },
				textureIndex
			));
			s_Data.VertexData[fontMaterial].push_back(new Vertex(
				{ xpos - width, ypos + height, pos.z },
				{ 1.0f, 1.0f, 1.0f, 1.0f },
				{ 0.0f, 0.0f },
				textureIndex
			));

			pos.x += (ch.Advance >> 6) * size.x;
		}
	}
}