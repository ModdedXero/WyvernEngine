#include "wvpch.h"
#include "Model3D.h"

#include <Wyvern/Core/Scene/Entity.h>
#include <Wyvern/Core/Components/MeshRenderer.h>
#include <Wyvern/Core/Components/MeshFilter.h>

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

namespace Wyvern::Render
{
	namespace Utils
	{
		static void CreateChildEntityFromMeshData(MeshData data, Entity& parent, Ref<Scene> scene)
		{
			Entity root = Scene::CreateEntity(scene);
			root.AddComponent<MeshRenderer>();
			root.AddComponent<MeshFilter>()->mesh = data.mesh;
			parent.AddChildEntity(root);

			for (auto& childMesh : data.childrenMeshes)
			{
				CreateChildEntityFromMeshData(childMesh, root, scene);
			}
		}

		static Mesh FindChildMesh(MeshData data, unsigned int index)
		{
			if (data.mesh.GetMeshIndex() == index)
				return data.mesh;

			for (auto& mesh : data.childrenMeshes)
			{
				if (mesh.mesh.GetMeshIndex() == index)
					return mesh.mesh;

				return FindChildMesh(mesh, index);
			}

			return Mesh();
		}
	}

	Model3D::Model3D(Tools::FileSystem path)
		: m_Path(path)
	{
		LoadModel();
	}

	void Model3D::GenerateEntity(Ref<Scene> scene)
	{
		Entity root = Scene::CreateEntity(scene);
		root.AddComponent<MeshRenderer>();
		root.AddComponent<MeshFilter>()->mesh = meshes.mesh;

		for (auto& meshData : meshes.childrenMeshes)
		{
			Utils::CreateChildEntityFromMeshData(meshData, root, scene);
		}
	}

	Mesh Model3D::GetMesh(unsigned int index)
	{
		if (meshes.mesh.m_Index == index)
			return meshes.mesh;

		for (auto& mesh : meshes.childrenMeshes)
		{
			return Utils::FindChildMesh(mesh, index);
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

		meshData.mesh = ProcessMesh(node, scene);

		for (uint32_t i = 0; i < node->mNumChildren; i++)
		{
			meshData.childrenMeshes.push_back(ProcessNode(node->mChildren[i], scene));
		}

		return meshData;
	}

	Mesh Model3D::ProcessMesh(aiNode* node, const aiScene* scene)
	{
		if (node->mNumMeshes == 0) return Mesh();

		Mesh wyvMesh;
		std::vector<Vector3> vertices;
		std::vector<Vector3> normals;
		std::vector<Vector2> uvs;
		std::vector<Vector4> colors;
		std::vector<int> indices;

		// Vertices and Normals

		for (uint32_t x = 0; x < node->mNumMeshes; x++)
		{
			size_t indiceStart = indices.size();
			aiMesh* mesh = scene->mMeshes[node->mMeshes[x]];

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
				{
					indices.push_back(face.mIndices[j]);
				}
			}

			wyvMesh.SetSubMesh(indiceStart, indiceStart - indices.size());

			// Materials/Textures/Colors

			if (mesh->mMaterialIndex >= 0)
			{
				aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];


				for (uint32_t i = 0; i < material->mNumProperties; i++)
				{
					// Color Map
					aiColor4D color;
					material->Get(AI_MATKEY_COLOR_DIFFUSE, color);

					Vector4 vColor;
					vColor.x = color.r;
					vColor.y = color.g;
					vColor.z = color.b;
					vColor.w = color.a;

					colors.push_back(vColor);
				}
			}
		}

		wyvMesh.vertices = vertices;
		wyvMesh.normals = normals;
		wyvMesh.uvs = uvs;
		wyvMesh.colors = colors;
		wyvMesh.indices = indices;
		wyvMesh.m_ModelPath = m_Path;
		wyvMesh.m_Index = node->mMeshes[0];

		return wyvMesh;
	}
}