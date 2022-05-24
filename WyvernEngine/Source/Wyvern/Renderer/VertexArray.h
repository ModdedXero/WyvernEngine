#pragma once

#include <Wyvern/Core/Math/Vector.h>
#include <Wyvern/Core/Graphics/Material.h>

namespace Wyvern::Renderer
{
	struct Vertex
	{
		Vertex() {}

		Vertex(Vector3 pos, Vector4 col, Vector2 coords, float texID, int entityID = -1)
		{
			this->Position = pos;
			this->Color = col;
			this->TexCoords = coords;
			this->TexID = texID;
			this->EntityID = entityID;
		}

		Vector3 Position;
		Vector4 Color;
		Vector2 TexCoords;
		float TexID = 0;
		int EntityID = -1;

		bool operator<(const Vertex& other)
		{
			return other.Position.z < Position.z;
		}
	};

	struct VertexArray
	{
		std::vector<Vertex> vertices;
		Ref<Material> material;

		VertexArray(Vertex vertices[4], Ref<Material> material)
		{
			this->vertices.push_back(vertices[0]);
			this->vertices.push_back(vertices[1]);
			this->vertices.push_back(vertices[2]);
			this->vertices.push_back(vertices[3]);

			this->material = material;
		}
	};
}