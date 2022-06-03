#include "wvpch.h"
#include "Renderer.h"
#include "Renderer2D.h"

#include "VertexArray.h"

#include <Wyvern/Core/AssetManager.h>
#include <Wyvern/Core/Application/Application.h>

#include <glad.h>

namespace Wyvern::Render
{
	Framebuffer* Renderer::s_Framebuffer;

	static const size_t MaxTriangleCount = 1000;
	static const size_t MaxVertexCount = MaxTriangleCount * 3;
	static const size_t MaxTextureCount = 32;

	struct RenderData
	{
		uint32_t VAO = 0;
		uint32_t VBO = 0;
		uint32_t IBO = 0;

		uint32_t SVAO = 0;
		uint32_t SVBO = 0;

		Shader ScreenShader;

		Vertex* VertexBuffer = nullptr;
		Vertex* VertexBufferPtr = nullptr;

		std::vector<int> IndexBuffer;

		uint32_t IndexOffset = 0;

		std::array<uint32_t, MaxTextureCount> TextureSlots;
		uint32_t TextureSlotIndex = 1;
		uint32_t WhiteTexture = 0;

		CameraRenderer* Camera = nullptr;
		Transform* CameraPosition = nullptr;
		Vector4 CameraClearColor = Vector4();
	};

	static RenderData s_Data;

	void Renderer::Construct()
	{
		// Framebuffer

		FramebufferSpecification fbSpec;
		fbSpec.Attachments =
		{
			FramebufferTextureFormat::RGBA8,
			FramebufferTextureFormat::RED_INTEGER,
			FramebufferTextureFormat::Depth
		};
		fbSpec.Width = 1280;
		fbSpec.Height = 720;
		s_Framebuffer = new Framebuffer(fbSpec);

		// Quad Renderer

		s_Data.VertexBuffer = new Vertex[MaxVertexCount];

		glGenVertexArrays(1, &s_Data.VAO);
		glBindVertexArray(s_Data.VAO);

		glGenBuffers(1, &s_Data.VBO);
		glBindBuffer(GL_ARRAY_BUFFER, s_Data.VBO);
		glBufferData(GL_ARRAY_BUFFER, MaxVertexCount * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);

		glEnableVertexArrayAttrib(s_Data.VAO, 0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, Position));

		glEnableVertexArrayAttrib(s_Data.VAO, 1);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, Color));

		glEnableVertexArrayAttrib(s_Data.VAO, 2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, TexCoords));

		glEnableVertexArrayAttrib(s_Data.VAO, 3);
		glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, TexID));

		glEnableVertexArrayAttrib(s_Data.VAO, 4);
		glVertexAttribIPointer(4, 1, GL_INT, sizeof(Vertex), (const void*)offsetof(Vertex, EntityID));

		glGenBuffers(1, &s_Data.IBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, s_Data.IBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * MaxVertexCount, nullptr, GL_DYNAMIC_DRAW);

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		// Screen Renderer

		float quadVertices[] = { // vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
	// positions   // texCoords
	-1.0f,  1.0f,  0.0f, 1.0f,
	-1.0f, -1.0f,  0.0f, 0.0f,
	 1.0f, -1.0f,  1.0f, 0.0f,

	-1.0f,  1.0f,  0.0f, 1.0f,
	 1.0f, -1.0f,  1.0f, 0.0f,
	 1.0f,  1.0f,  1.0f, 1.0f
		};

		glGenVertexArrays(1, &s_Data.SVAO);
		glGenBuffers(1, &s_Data.SVBO);
		glBindVertexArray(s_Data.SVAO);
		glBindBuffer(GL_ARRAY_BUFFER, s_Data.SVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		s_Data.ScreenShader = Shader(Application::GetResourcesPath() / "/Shader/ScreenShader.glsl");
		s_Data.ScreenShader.SetInteger("screenTexture", 0);

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
		for (size_t i = 1; i < MaxTextureCount; i++)
			s_Data.TextureSlots[i] = 0;

		// OpenGL Settings
		glEnable(GL_DEPTH_TEST);
	}

	void Renderer::Destruct()
	{
		glDeleteVertexArrays(1, &s_Data.VAO);
		glDeleteVertexArrays(1, &s_Data.SVAO);
		glDeleteBuffers(1, &s_Data.SVBO);
		glDeleteBuffers(1, &s_Data.VBO);
		glDeleteBuffers(1, &s_Data.IBO);

		delete[] s_Data.VertexBuffer;
	}

	void Renderer::BeginScene(CameraRenderer* cameraRenderer, Transform* cameraPosition, Vector4 clearColor)
	{
		s_Framebuffer->Invalidate();
		s_Framebuffer->Bind();
		s_Framebuffer->ClearColorAttachment(1, -1);

		s_Data.Camera = cameraRenderer;
		s_Data.CameraPosition = cameraPosition;
		s_Data.CameraClearColor = clearColor;
		s_Data.Camera->Resize(s_Framebuffer->GetSpecification().Width, s_Framebuffer->GetSpecification().Height);

		glClearColor(s_Data.CameraClearColor.x, s_Data.CameraClearColor.y, s_Data.CameraClearColor.z, s_Data.CameraClearColor.w);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		Renderer2D::BeginScene(cameraRenderer, cameraPosition, clearColor);

		BeginBatch();
	}

	void Renderer::EndScene()
	{
		EndBatch();
		Flush();

		Renderer2D::EndScene();

		s_Framebuffer->Unbind();

#ifndef WV_DEBUG
		glDisable(GL_DEPTH_TEST);
		glClear(GL_COLOR_BUFFER_BIT);
		AssetManager::GetShader("ScreenShader")->Use();
		glBindVertexArray(s_Data.SVAO);
		s_Framebuffer->BindColorAttachmentTexture();
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);
#endif
	}

	void Renderer::DrawMesh(Transform* transform, Ref<Material> material, Mesh* mesh, const Vector4& color, int entityID)
	{
		DrawMesh(transform, material, mesh->vertices, mesh->uvs, mesh->indices, color, entityID);
	}

	void Renderer::DrawMesh(Transform* transform, Ref<Material> material, std::vector<Vector3> vertices, std::vector<Vector2> uvs, std::vector<int> indices, const Vector4& color, int entityID)
	{
		if (s_Data.IndexBuffer.size() >= MaxVertexCount)
		{
			EndBatch();
			Flush();
			BeginBatch();
		}

		if (!material) return;

		material->GetShader().Use();
		s_Data.Camera->SetShaderMatrices(material->GetShader(), s_Data.CameraPosition);

		float textureIndex = 0.0f;
		Vector2 textureCoords = Vector2(0.0f, 0.0f);

		Matrix4x4 matrix = Matrix4x4::Translate(transform->GlobalPosition()) 
			* Matrix4x4::Rotate(transform->GlobalRotation())
			* Matrix4x4::Scale(transform->GlobalScale());

		for (Vector3& position : vertices)
		{
			Vector3 vertex = matrix * glm::vec4(position.x, position.y, position.z, 1.0f);

			s_Data.VertexBufferPtr->Position = vertex;
			s_Data.VertexBufferPtr->Color = color;
			s_Data.VertexBufferPtr->TexCoords = textureCoords;
			s_Data.VertexBufferPtr->TexID = textureIndex;
			s_Data.VertexBufferPtr->EntityID = entityID;
			s_Data.VertexBufferPtr++;
		}

		for (int indice : indices)
		{
			s_Data.IndexBuffer.push_back(indice + s_Data.IndexOffset);
		}

		s_Data.IndexOffset += vertices.size();
	}

	void Renderer::BeginBatch()
	{
		s_Data.VertexBufferPtr = s_Data.VertexBuffer;
		s_Data.IndexBuffer.clear();
	}

	void Renderer::EndBatch()
	{
		if (s_Data.IndexBuffer.size() <= 0) return;

		GLsizeiptr size = (uint8_t*)s_Data.VertexBufferPtr - (uint8_t*)s_Data.VertexBuffer;
		glBindBuffer(GL_ARRAY_BUFFER, s_Data.VBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, size, s_Data.VertexBuffer);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, s_Data.IBO);
		glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(s_Data.IndexBuffer) * s_Data.IndexBuffer.size(), &s_Data.IndexBuffer.front());
	}

	void Renderer::Flush()
	{
		s_Data.IndexOffset = 0;

		if (s_Data.IndexBuffer.size() <= 0) return;

		for (uint32_t i = 0; i < s_Data.TextureSlotIndex; i++)
			glBindTextureUnit(i, s_Data.TextureSlots[i]);

		glBindVertexArray(s_Data.VAO);
		glDrawElements(GL_TRIANGLES, s_Data.IndexBuffer.size(), GL_UNSIGNED_INT, nullptr);

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}