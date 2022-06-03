#include "wvpch.h"
#include "AssetManager.h"

#include <stb_image.h>

namespace Wyvern
{
	std::unordered_map<std::string, Ref<Texture2D>> s_Textures;
	std::unordered_map<std::string, Ref<Sprite>> s_SubTextures;
	std::unordered_map<std::string, Ref<Material>> s_Materials;

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
		s_SubTextures[name] = Sprite::CreateFromCoords(GetTexture(textureName), coords, tileSize, spriteSize);
		return s_SubTextures[name];
	}

	Ref<Sprite> AssetManager::GetSprite(std::string name)
	{
		return s_SubTextures[name];
	}

	Ref<Material> AssetManager::LoadMaterial(std::string shader, std::string name)
	{
		Ref<Material> mat = CreateRef<Material>();
		mat->shader = GetShader(shader);
		s_Materials[name] = mat;
		return s_Materials[name];
	}

	Ref<Material> AssetManager::GetMaterial(std::string name)
	{
		return s_Materials[name];
	}

	Ref<Material> AssetManager::GetDefaultMaterial()
	{
		return s_Materials.begin()->second;
	}

	void AssetManager::Clear()
	{
		for (auto& iter : s_Shaders)
			glDeleteProgram(iter.second->ID);

		for (auto& iter : s_Textures)
			glDeleteProgram(iter.second->GetID());
	}
}
