#pragma once

#include <Wyvern/Core/Scene/Scene.h>
#include <Wyvern/Core/Graphics/Mesh.h>
#include <Wyvern/Tools/FileSystem.h>

#include <assimp/scene.h>

struct aiNode;
struct aiMesh;

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
		Model3D(Tools::FileSystem path);

		void GenerateEntity(Ref<Scene> scene);
		Mesh GetMesh(unsigned int index);

		MeshData meshes;

	private:
		Tools::FileSystem m_Path;
		aiScene* m_Scene;

	private:
		void LoadModel();
		MeshData ProcessNode(aiNode* node, const aiScene* scene);
		Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene, unsigned int index);
	};
}