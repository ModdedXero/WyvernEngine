#pragma once

#include <Wyvern/Core/Graphics/Mesh.h>
#include <Wyvern/Utils/FileSystem.h>

namespace Wyvern::Render
{
	class MeshImporter
	{
	public:
		static Mesh ImportMesh(Utils::FileSystem& path);
	};
}