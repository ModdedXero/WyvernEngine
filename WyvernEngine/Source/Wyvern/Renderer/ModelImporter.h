#pragma once

#include <Wyvern/Core/Scene/Scene.h>
#include <Wyvern/Core/Graphics/Mesh.h>
#include <Wyvern/Core/Graphics/Material.h>
#include <Wyvern/Tools/FileSystem.h>

#include <assimp/scene.h>

struct aiNode;

namespace Wyvern::Render
{
	struct MeshData
	{
		Mesh mesh;
		std::vector<Material> materials;
		std::vector<MeshData> childrenMeshes;
	};

	class ModelImporter
	{
	public:
		ModelImporter(Tools::FileSystem path);

		void GenerateEntity(Ref<Scene> scene);
		Mesh GetMesh(unsigned int index);

		MeshData meshes;

	private:
		Tools::FileSystem m_Path;
		aiScene* m_Scene;

	private:
		void LoadModel();
		MeshData ProcessNode(aiNode* node, const aiScene* scene);
		Mesh ProcessMesh(aiNode* node, const aiScene* scene);
		std::vector<Material> ProcessMaterials(aiNode* node, const aiScene* scene);
	};
}