#pragma once

#include <Wyvern/Core/Math/Vector.h>

#include <vector>

namespace Wyvern
{
	struct Mesh
	{
	public:
		std::vector<Vector3> vertices;
		std::vector<Vector3> normals;
		std::vector<int> indices;
		std::vector<uint32_t> textures;
		std::vector<Vector2> uvs;
	};
}