#pragma once

#include <Wyvern/Core/Math/Vector.h>
#include <Wyvern/Tools/FileSystem.h>

#include <vector>

namespace Wyvern
{
	namespace Render
	{
		class ModelImporter;
	}

	struct SubMesh
	{
	public:
		size_t start;
		size_t count;
	};

	struct Mesh
	{
		friend class Render::ModelImporter;
	public:
		std::vector<Vector3> vertices;
		std::vector<Vector3> normals;
		std::vector<Vector2> uvs;
		std::vector<Vector4> colors;
		std::vector<int> indices;

		Tools::FileSystem GetModelPath() const { return m_ModelPath; }
		uint32_t GetMeshIndex() const { return m_Index; }
		uint32_t GetSubMeshCount() const { return m_SubMeshes.size(); }
		Mesh GetSubMesh(size_t index);

		void SetSubMesh(size_t start, size_t count);

	private:
		Tools::FileSystem m_ModelPath;
		int m_Index = -1;

		std::vector<SubMesh> m_SubMeshes;
	};
}