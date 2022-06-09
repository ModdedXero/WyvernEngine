#include "wvpch.h"
#include "Mesh.h"

namespace Wyvern
{
	Mesh Mesh::GetSubMesh(size_t index)
	{
		if (index >= m_SubMeshes.size()) return Mesh();

		Mesh mesh;
		SubMesh subMesh = m_SubMeshes[index];

		if (vertices.size())	mesh.vertices = std::vector<Vector3>(vertices.begin() + subMesh.start, vertices.begin() + subMesh.count + 1);
		if (uvs.size())			mesh.uvs = std::vector<Vector2>(uvs.begin() + subMesh.start, uvs.begin() + subMesh.count + 1);
		if (indices.size())		mesh.indices = std::vector<int>(indices.begin() + subMesh.start, indices.begin() + subMesh.count + 1);
		if (colors.size())		mesh.colors = std::vector<Vector4>(colors.begin() + subMesh.start, colors.begin() + subMesh.count + 1);

		return mesh;
	}

	void Mesh::SetSubMesh(size_t start, size_t count)
	{
		m_SubMeshes.push_back({ start, count });
	}
}