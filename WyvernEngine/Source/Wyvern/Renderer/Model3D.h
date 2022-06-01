#pragma once

#include <Wyvern/Core/Graphics/Mesh.h>
#include <Wyvern/Tools/FileSystem.h>

struct aiNode;
struct aiMesh;
struct aiScene;

namespace Wyvern::Render
{
	struct MeshData
	{
		Mesh rootMesh;
		std::vector<MeshData> childrenMeshes;
	};

	class Model3D
	{
	public:
		Model3D(Tools::FileSystem& path);

		MeshData meshes;
	private:
		Tools::FileSystem m_Path;

	private:
		void LoadModel();
		MeshData ProcessNode(aiNode* node, const aiScene* scene);
		Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
	};
}