#include "mlpch.h"
#include "ResourceManager.h"

#include <stb_image.h>

namespace Merlin
{
	std::unordered_map<const char*, Shader*> s_Shaders;
	std::unordered_map<const char*, Texture2D*> s_Textures;
	std::unordered_map<const char*, SubTexture2D*> s_SubTextures;

	Shader* ResourceManager::LoadShader(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile, const char* name)
	{
		s_Shaders[name] = loadShaderFromFile(vShaderFile, fShaderFile, gShaderFile);
		s_Shaders[name]->Use();
		int samplers[32];
		for (int i = 0; i < 32; i++)
			samplers[i] = i;
		s_Shaders[name]->SetIntArray("uTextures", 32, samplers);
		return s_Shaders[name];
	}

	Shader* ResourceManager::GetShader(const char* name)
	{
		return s_Shaders[name];
	}

	Texture2D* ResourceManager::LoadTexture(const char* file, bool alpha, bool pixel, const char* name)
	{
		s_Textures[name] = loadTexture2DFromFile(file, alpha, pixel);
		return s_Textures[name];
	}

	Texture2D* ResourceManager::GetTexture(const char* name)
	{
		return s_Textures[name];
	}

	SubTexture2D* ResourceManager::LoadSubTexture(const char* name, const char* textureName, const Vector2& coords, const Vector2& tileSize, const Vector2& spriteSize)
	{
		s_SubTextures[name] = SubTexture2D::CreateFromCoords(GetTexture(textureName), coords, tileSize, spriteSize);
		return s_SubTextures[name];
	}

	SubTexture2D* ResourceManager::GetSubTexture(const char* name)
	{
		return s_SubTextures[name];
	}

	void ResourceManager::Clear()
	{
		for (auto& iter : s_Shaders)
			glDeleteProgram(iter.second->ID);

		for (auto& iter : s_Textures)
			glDeleteProgram(iter.second->ID);
	}

	std::unordered_map<const char*, Shader*> ResourceManager::GetShaders()
	{
		return s_Shaders;
	}

	std::unordered_map<const char*, Texture2D*> ResourceManager::GetTextures()
	{
		return s_Textures;
	}

	std::unordered_map<const char*, SubTexture2D*> ResourceManager::GetSubTextures()
	{
		return s_SubTextures;
	}

	Shader* ResourceManager::loadShaderFromFile(const char* vShaderPath, const char* fShaderPath, const char* gShaderPath)
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

		return new Shader(vShaderCode, fShaderCode, gShaderPath != nullptr ? gShaderCode : nullptr);
	}

	Texture2D* ResourceManager::loadTexture2DFromFile(const char* texturePath, bool alpha, bool pixel)
	{
		Texture2D* texture = new Texture2D();

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
