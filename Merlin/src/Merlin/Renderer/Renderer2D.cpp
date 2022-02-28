#include "mlpch.h"
#include "Renderer2D.h"

#include <glad.h>

namespace Merlin
{
	static const size_t MaxQuadCount = 1000;
	static const size_t MaxVertexCount = MaxQuadCount * 4;
	static const size_t MaxIndexCount = MaxQuadCount * 6;

	struct Vertex
	{
		Vector3 Position;
		Vector4 Color;
		Vector2 TexCoords;
		float TexID;
	};

	struct RenderData
	{
		GLuint VAO = 0;
		GLuint VBO = 0;
		GLuint IBO = 0;

		Vertex* QuadBuffer = nullptr;
		Vertex* QuadBufferPtr = nullptr;

		uint32_t IndexCount = 0;
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
}