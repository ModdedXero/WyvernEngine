#include "wvpch.h"
#include "AssetManager.h"

#include <stb_image.h>

namespace Wyvern
{
	std::unordered_map<std::string, Ref<Shader>> s_Shaders;
	std::unordered_map<std::string, Ref<Texture2D>> s_Textures;
	std::unordered_map<std::string, Ref<Sprite>> s_SubTextures;
	std::unordered_map<std::string, Ref<Material>> s_Materials;

	Ref<Shader> AssetManager::LoadShader(Tools::FileSystem vShaderFile, Tools::FileSystem fShaderFile, Tools::FileSystem gShaderFile, std::string name)
	{
		s_Shaders[name] = loadShaderFromFile(vShaderFile, fShaderFile, gShaderFile);
		s_Shaders[name]->Use();
		int samplers[32];
		for (int i = 0; i < 32; i++)
			samplers[i] = i;
		s_Shaders[name]->SetIntArray("uTextures", 32, samplers);
		return s_Shaders[name];
	}

	Ref<Shader> AssetManager::GetShader(std::string name)
	{
		return s_Shaders[name];
	}

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

	Ref<Shader> AssetManager::loadShaderFromFile(std::string vShaderPath, std::string fShaderPath, std::string gShaderPath)
	{
		std::string vertCode, fragCode, geoCode;

		try
		{
			std::ifstream vertShaderFile(vShaderPath);
			std::ifstream fragShaderFile(fShaderPath);
			std::stringstream vs_Shaderstream, fs_Shaderstream;

			vs_Shaderstream << vertShaderFile.rdbuf();
			fs_Shaderstream << fragShaderFile.rdbuf();

			vertShaderFile.close();
			fragShaderFile.close();

			vertCode = vs_Shaderstream.str();
			fragCode = fs_Shaderstream.str();

			if (!gShaderPath.empty())
			{
				std::ifstream geoShaderFile(gShaderPath);
				std::stringstream gs_Shaderstream;
				gs_Shaderstream << geoShaderFile.rdbuf();
				geoShaderFile.close();
				geoCode = gs_Shaderstream.str();
			}
		}
		catch (const std::exception& e)
		{
			DEBUG_LOG_ERROR("ResourceManager: ", e.what());
		}

		const char* vShaderCode = vertCode.c_str();
		const char* fShaderCode = fragCode.c_str();
		const char* gShaderCode = geoCode.c_str();

		return CreateRef<Shader>(vShaderCode, fShaderCode, !gShaderPath.empty() ? gShaderCode : nullptr);
	}
}
