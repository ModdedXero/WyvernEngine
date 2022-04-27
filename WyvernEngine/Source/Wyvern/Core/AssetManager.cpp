#include "wvpch.h"
#include "AssetManager.h"

#include <stb_image.h>

namespace Wyvern
{
	std::unordered_map<const char*, Ref<Shader>> s_Shaders;
	std::unordered_map<const char*, Ref<Texture2D>> s_Textures;
	std::unordered_map<const char*, Ref<Sprite>> s_SubTextures;
	std::unordered_map<const char*, Ref<Material>> s_Materials;

	Ref<Shader> AssetManager::LoadShader(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile, const char* name)
	{
		s_Shaders[name] = loadShaderFromFile(vShaderFile, fShaderFile, gShaderFile);
		s_Shaders[name]->Use();
		int samplers[32];
		for (int i = 0; i < 32; i++)
			samplers[i] = i;
		s_Shaders[name]->SetIntArray("uTextures", 32, samplers);
		return s_Shaders[name];
	}

	Ref<Shader> AssetManager::GetShader(const char* name)
	{
		return s_Shaders[name];
	}

	Ref<Texture2D> AssetManager::LoadTexture(const char* file, bool alpha, bool pixel, const char* name)
	{
		s_Textures[name] = loadTexture2DFromFile(file, alpha, pixel);
		return s_Textures[name];
	}

	Ref<Texture2D> AssetManager::GetTexture(const char* name)
	{
		return s_Textures[name];
	}

	Ref<Sprite> AssetManager::LoadSprite(const char* name, const char* textureName, const Vector2& coords, const Vector2& tileSize, const Vector2& spriteSize)
	{
		s_SubTextures[name] = Sprite::CreateFromCoords(GetTexture(textureName), coords, tileSize, spriteSize);
		return s_SubTextures[name];
	}

	Ref<Sprite> AssetManager::GetSprite(const char* name)
	{
		return s_SubTextures[name];
	}

	Ref<Material> AssetManager::LoadMaterial(const char* shader, const char* name)
	{
		Ref<Material> mat = CreateRef<Material>();
		mat->shader = GetShader(shader);
		s_Materials[name] = mat;
		return s_Materials[name];
	}

	Ref<Material> AssetManager::GetMaterial(const char* name)
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
			glDeleteProgram(iter.second->ID);
	}

	Ref<Shader> AssetManager::loadShaderFromFile(const char* vShaderPath, const char* fShaderPath, const char* gShaderPath)
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

			if (gShaderPath != nullptr)
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

		return CreateRef<Shader>(vShaderCode, fShaderCode, gShaderPath != nullptr ? gShaderCode : nullptr);
	}

	Ref<Texture2D> AssetManager::loadTexture2DFromFile(const char* texturePath, bool alpha, bool pixel)
	{
		Ref<Texture2D> texture = CreateRef<Texture2D>();

		if (alpha)
		{
			texture->InternalFormat = GL_RGBA;
			texture->ImageFormat = GL_RGBA;
		}

		if (pixel)
		{
			texture->FilterMin = GL_NEAREST;
			texture->FilterMax = GL_NEAREST;
		}

		int width, height, nrChannels;
		unsigned char* data = stbi_load(texturePath, &width, &height, &nrChannels, 0);

		texture->Generate(width, height, data);

		stbi_image_free(data);
		return texture;
	}

}
