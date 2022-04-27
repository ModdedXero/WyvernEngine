#pragma once

#include <Wyvern/Core/Math/Vector.h>

namespace Wyvern::Renderer
{
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

		bool operator<(const Vertex& other)
		{
			return other.Position.z < Position.z;
		}
	};

	struct VertexArray
	{
		Vertex vertices[4];
		Ref<Material> material;

		VertexArray(Vertex vertices[4], Ref<Material> material)
		{
			this->vertices[0] = vertices[0];
			this->vertices[1] = vertices[1];
			this->vertices[2] = vertices[2];
			this->vertices[3] = vertices[3];

			this->material = material;
		}
	};
}