#pragma once

#include <Wyvern/Core/Math/Vector.h>
#include <Wyvern/Tools/FileSystem.h>

#include <vector>

namespace Wyvern
{
	namespace Render
	{
		class Model3D;
	}

	struct Mesh
	{
		friend class Render::Model3D;
	public:
		std::vector<Vector3> vertices;
		std::vector<Vector3> normals;
		std::vector<int> indices;
		std::vector<uint32_t> textures;
		std::vector<Vector2> uvs;

		Tools::FileSystem GetModelPath() const { return m_ModelPath; }
		unsigned int GetMeshIndex() const { return m_Index; }

	private:
		Tools::FileSystem m_ModelPath;
		unsigned int m_Index;
	};
}