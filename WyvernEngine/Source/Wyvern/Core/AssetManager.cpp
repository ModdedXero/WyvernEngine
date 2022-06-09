#include "wvpch.h"
#include "AssetManager.h"

#include <stb_image.h>

namespace Wyvern
{
	std::unordered_map<std::string, Ref<Texture2D>> s_Textures;
	std::unordered_map<std::string, Ref<Sprite>> s_Sprites;
	std::unordered_map<UUID, Ref<Material>> s_Materials;

	Ref<Texture2D> AssetManager::LoadTexture(Ref<Texture2D> texture, std::string name)
	{
		s_Textures[name] = texture;
		return s_Textures[name];
	}

	Ref<Texture2D> AssetManager::GetTexture(std::string name)
	{
		return s_Textures[name];
	}

	Ref<Sprite> AssetManager::LoadSprite(std::string name, std::string textureName, const Vector2& coords, const Vector2& tileSize, const Vector2& spriteSize)
	{
		s_Sprites[name] = Sprite::CreateFromCoords(GetTexture(textureName), coords, tileSize, spriteSize);
		return s_Sprites[name];
	}

	Ref<Sprite> AssetManager::GetSprite(std::string name)
	{
		return s_Sprites[name];
	}

	Ref<Material> AssetManager::LoadMaterial(Tools::FileSystem& material)
	{
		Ref<Material> mat = CreateRef<Material>(material);
		s_Materials[mat->uuid] = mat;
		return s_Materials[mat->uuid];
	}

	Ref<Material> AssetManager::LoadMaterial(Material material)
	{
		Ref<Material> mat = CreateRef<Material>(material);
		s_Materials[mat->uuid] = mat;
		return s_Materials[mat->uuid];
	}

	Ref<Material> AssetManager::GetMaterial(UUID& uuid)
	{
		return s_Materials[uuid];
	}

	Ref<Material> AssetManager::GetDefaultMaterial()
	{
		return s_Materials.begin()->second;
	}

	uint32_t AssetManager::GetStandardShader()
	{
		return GetDefaultMaterial()->GetShader().ID;
	}

	void AssetManager::Clear()
	{
		for (auto& iter : s_Textures)
			glDeleteProgram(iter.second->GetID());

		for (auto& iter : s_Materials)
			glDeleteProgram(iter.second->GetShader().ID);
	}
}
