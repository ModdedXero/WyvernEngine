#include "mlpch.h"
#include "Renderer2D.h"

#include <glad.h>

namespace Merlin::Renderer
{
	static const size_t MaxQuadCount = 1000;
	static const size_t MaxVertexCount = MaxQuadCount * 4;
	static const size_t MaxIndexCount = MaxQuadCount * 6;
	static const size_t MaxTextures = 32;

	struct Vertex
	{
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

		uint32_t IndexCount = 0;

		std::array<uint32_t, MaxTextures> TextureSlots;
		uint32_t TextureSlotIndex = 1;

		uint32_t WhiteTexture = 0;
	};

	static RenderData s_Data;

	void Renderer2D::OnAwake()
	{
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
	}

	void Renderer2D::OnDestroy()
	{
		glDeleteVertexArrays(1, &s_Data.VAO);
		glDeleteBuffers(1, &s_Data.VBO);
		glDeleteBuffers(1, &s_Data.IBO);

		delete[] s_Data.QuadBuffer;
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

	void Renderer2D::DrawQuad(const Vector3& pos, const Vector2& size, const Vector4& color)
	{
		if (s_Data.IndexCount >= MaxIndexCount)
		{
			EndBatch();
			Flush();
			BeginBatch();
		}

		s_Data.QuadBufferPtr->Position = { pos.x - size.x, pos.y - size.y, pos.z };
		s_Data.QuadBufferPtr->Color = color;
		s_Data.QuadBufferPtr->TexCoords = { 0.0f, 0.0f };
		s_Data.QuadBufferPtr->TexID = 0.0f;
		s_Data.QuadBufferPtr++;

		s_Data.QuadBufferPtr->Position = { pos.x + size.x, pos.y - size.y, pos.z };
		s_Data.QuadBufferPtr->Color = color;
		s_Data.QuadBufferPtr->TexCoords = { 0.0f, 0.0f };
		s_Data.QuadBufferPtr->TexID = 0.0f;
		s_Data.QuadBufferPtr++;

		s_Data.QuadBufferPtr->Position = { pos.x + size.x, pos.y + size.y, pos.z };
		s_Data.QuadBufferPtr->Color = color;
		s_Data.QuadBufferPtr->TexCoords = { 0.0f, 0.0f };
		s_Data.QuadBufferPtr->TexID = 0.0f;
		s_Data.QuadBufferPtr++;

		s_Data.QuadBufferPtr->Position = { pos.x - size.x, pos.y + size.y, pos.z };
		s_Data.QuadBufferPtr->Color = color;
		s_Data.QuadBufferPtr->TexCoords = { 0.0f, 0.0f };
		s_Data.QuadBufferPtr->TexID = 0.0f;
		s_Data.QuadBufferPtr++;

		s_Data.IndexCount += 6;
	}

	void Renderer2D::DrawQuad(const Vector3& pos, const Vector2& size, uint32_t& textureID)
	{
		if (s_Data.IndexCount >= MaxIndexCount || s_Data.TextureSlotIndex > (MaxTextures - 1))
		{
			EndBatch();
			Flush();
			BeginBatch();
		}

		const Vector4 color = { 1.0f, 1.0f, 1.0f, 1.0f };

		float textureIndex = 0.0f;
		for (uint32_t i = 1; i < s_Data.TextureSlotIndex; i++)
		{
			if (s_Data.TextureSlots[i] == textureID)
			{
				textureIndex = (float)i;
				break;
			}
		}

		if (textureIndex == 0.0f)
		{
			textureIndex = (float)s_Data.TextureSlotIndex;
			s_Data.TextureSlots[s_Data.TextureSlotIndex] = textureID;
			s_Data.TextureSlotIndex++;
		}

		s_Data.QuadBufferPtr->Position = { pos.x - size.x, pos.y - size.y, pos.z };
		s_Data.QuadBufferPtr->Color = color;
		s_Data.QuadBufferPtr->TexCoords = { 0.0f, 0.0f };
		s_Data.QuadBufferPtr->TexID = textureIndex;
		s_Data.QuadBufferPtr++;

		s_Data.QuadBufferPtr->Position = { pos.x + size.x, pos.y - size.y, pos.z };
		s_Data.QuadBufferPtr->Color = color;
		s_Data.QuadBufferPtr->TexCoords = { 1.0f, 0.0f };
		s_Data.QuadBufferPtr->TexID = textureIndex;
		s_Data.QuadBufferPtr++;

		s_Data.QuadBufferPtr->Position = { pos.x + size.x, pos.y + size.y, pos.z };
		s_Data.QuadBufferPtr->Color = color;
		s_Data.QuadBufferPtr->TexCoords = { 1.0f, 1.0f };
		s_Data.QuadBufferPtr->TexID = textureIndex;
		s_Data.QuadBufferPtr++;

		s_Data.QuadBufferPtr->Position = { pos.x - size.x, pos.y + size.y, pos.z };
		s_Data.QuadBufferPtr->Color = color;
		s_Data.QuadBufferPtr->TexCoords = { 0.0f, 1.0f };
		s_Data.QuadBufferPtr->TexID = textureIndex;
		s_Data.QuadBufferPtr++;

		s_Data.IndexCount += 6;
	}

	void Renderer2D::DrawQuad(const Vector3& pos, const Vector2& size, SubTexture2D& subTexture)
	{
		if (s_Data.IndexCount >= MaxIndexCount || s_Data.TextureSlotIndex > (MaxTextures - 1))
		{
			EndBatch();
			Flush();
			BeginBatch();
		}

		const Vector4 color = { 1.0f, 1.0f, 1.0f, 1.0f };

		float textureIndex = 0.0f;
		for (uint32_t i = 1; i < s_Data.TextureSlotIndex; i++)
		{
			if (s_Data.TextureSlots[i] == subTexture.GetTexture().ID)
			{
				textureIndex = (float)i;
				break;
			}
		}

		if (textureIndex == 0.0f)
		{
			textureIndex = (float)s_Data.TextureSlotIndex;
			s_Data.TextureSlots[s_Data.TextureSlotIndex] = subTexture.GetTexture().ID;
			s_Data.TextureSlotIndex++;
		}

		s_Data.QuadBufferPtr->Position = { pos.x - size.x, pos.y - size.y, pos.z };
		s_Data.QuadBufferPtr->Color = color;
		s_Data.QuadBufferPtr->TexCoords = subTexture.GetTexCoords()[3];
		s_Data.QuadBufferPtr->TexID = textureIndex;
		s_Data.QuadBufferPtr++;

		s_Data.QuadBufferPtr->Position = { pos.x + size.x, pos.y - size.y, pos.z };
		s_Data.QuadBufferPtr->Color = color;
		s_Data.QuadBufferPtr->TexCoords = subTexture.GetTexCoords()[2];
		s_Data.QuadBufferPtr->TexID = textureIndex;
		s_Data.QuadBufferPtr++;

		s_Data.QuadBufferPtr->Position = { pos.x + size.x, pos.y + size.y, pos.z };
		s_Data.QuadBufferPtr->Color = color;
		s_Data.QuadBufferPtr->TexCoords = subTexture.GetTexCoords()[1];
		s_Data.QuadBufferPtr->TexID = textureIndex;
		s_Data.QuadBufferPtr++;

		s_Data.QuadBufferPtr->Position = { pos.x - size.x, pos.y + size.y, pos.z };
		s_Data.QuadBufferPtr->Color = color;
		s_Data.QuadBufferPtr->TexCoords = subTexture.GetTexCoords()[0];
		s_Data.QuadBufferPtr->TexID = textureIndex;
		s_Data.QuadBufferPtr++;

		s_Data.IndexCount += 6;
	}
}