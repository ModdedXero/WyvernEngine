#include "wvpch.h"
#include "Mesh.h"

namespace Wyvern
{
	Mesh Mesh::GetSubMesh(size_t index)
	{
		return Mesh();
	}

	void Mesh::SetSubMesh(size_t start, size_t count)
	{
		m_SubMeshes.push_back({ start, count });
	}
}