#pragma once

#include <Wyvern/Core/Math/Vector.h>

#include <vector>

namespace Wyvern
{
	struct Mesh
	{
	public:
		std::vector<Vector3> vertices;
		std::vector<Vector2> uvs;
		std::vector<int> indices;
	};
}