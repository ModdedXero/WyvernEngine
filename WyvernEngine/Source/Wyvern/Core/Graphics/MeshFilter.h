#pragma once

#include "Mesh.h"

#include <Wyvern/Utils/FileSystem.h>

namespace Wyvern
{
	struct MeshFilter
	{
	public:
		Mesh mesh;

		MeshFilter() {}

		MeshFilter(Utils::FileSystem meshPath)
		{
			m_MeshPath = meshPath;
		}

		void LoadMesh() {}
		void LoadMesh(Utils::FileSystem meshPath) {}

		Utils::FileSystem GetMeshPath() const { return m_MeshPath; }

	private:
		Utils::FileSystem m_MeshPath;
	};
}