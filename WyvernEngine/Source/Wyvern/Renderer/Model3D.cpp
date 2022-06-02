#include "wvpch.h"
#include "Model3D.h"

#include <Wyvern/Core/Scene/Entity.h>
#include <Wyvern/Core/Components/MeshRenderer.h>
#include <Wyvern/Core/Components/MeshFilter.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace Wyvern::Render
{
	namespace Utils
	{
		static void CreateChildEntityFromMeshData(MeshData data, Entity& parent, Ref<Scene> scene)
		{
			Entity root = Scene::CreateEntity(scene);
			root.AddComponent<MeshRenderer>();
			root.AddComponent<MeshFilter>()->mesh = data.rootMesh;
			parent.AddChildEntity(root);

			for (auto& childMesh : data.childrenMeshes)
			{
				CreateChildEntityFromMeshData(childMesh, root, scene);
			}
		}
	}

	Model3D::Model3D(Tools::FileSystem& path)
		: m_Path(path)
	{
		LoadModel();
	}

	void Model3D::GenerateEntity(Ref<Scene> scene)
	{
		Entity root = Scene::CreateEntity(scene);
		root.AddComponent<MeshRenderer>();
		root.AddComponent<MeshFilter>()->mesh = meshes.rootMesh;

		for (auto& meshData : meshes.childrenMeshes)
		{
			Utils::CreateChildEntityFromMeshData(meshData, root, scene);
		}
	}

	void Model3D::LoadModel()
	{
		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(m_Path, aiProcess_Triangulate | aiProcess_FlipUVs);

		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			DEBUG_CORE_ERROR(importer.GetErrorString());
			return;
		}

		meshes = ProcessNode(scene->mRootNode, scene);
	}

	MeshData Model3D::ProcessNode(aiNode* node, const aiScene* scene)
	{
		MeshData meshData;

		if (node->mMeshes)
		{
			aiMesh* mesh = scene->mMeshes[node->mMeshes[0]];
			meshData.rootMesh = ProcessMesh(mesh, scene);
		}

		for (uint32_t i = 0; i < node->mNumChildren; i++)
		{
			meshData.childrenMeshes.push_back(ProcessNode(node->mChildren[i], scene));
		}

		return meshData;
	}

	Mesh Model3D::ProcessMesh(aiMesh* mesh, const aiScene* scene)
	{
		std::vector<Vector3> vertices;
		std::vector<Vector3> normals;
		std::vector<Vector2> uvs;
		std::vector<uint32_t> textures;
		std::vector<int> indices;

		// Vertices and Normals

		for (uint32_t i = 0; i < mesh->mNumVertices; i++)
		{
			Vector3 position;

			position.x = mesh->mVertices[i].x;
			position.y = mesh->mVertices[i].y;
			position.z = mesh->mVertices[i].z;

			vertices.push_back(position);

			Vector3 normal;

			normal.x = mesh->mNormals[i].x;
			normal.y = mesh->mNormals[i].y;
			normal.z = mesh->mNormals[i].z;

			normals.push_back(normal);

			// Texture Coords

			if (mesh->mTextureCoords[0])
			{
				Vector2 texCoords;

				texCoords.x = mesh->mTextureCoords[0][i].x;
				texCoords.y = mesh->mTextureCoords[0][i].y;

				uvs.push_back(texCoords);
			}
			else
			{
				uvs.push_back({ 0, 0 });
			}
		}

		// Indices

		for (uint32_t i = 0; i < mesh->mNumFaces; i++)
		{
			aiFace face = mesh->mFaces[i];
			for (uint32_t j = 0; j < face.mNumIndices; j++)
				indices.push_back(face.mIndices[j]);
		}

		// Materials/Textures

		if (mesh->mMaterialIndex >= 0)
		{
			aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
		}

		Mesh wyvMesh;
		wyvMesh.vertices = vertices;
		wyvMesh.normals = normals;
		wyvMesh.indices = indices;
		wyvMesh.textures = textures;
		wyvMesh.uvs = uvs;

		return wyvMesh;
	}
}