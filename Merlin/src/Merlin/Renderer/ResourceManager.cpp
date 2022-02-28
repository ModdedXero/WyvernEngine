#include "mlpch.h"
#include "ResourceManager.h"

#include <stb_image.h>

namespace Merlin
{
	std::unordered_map<const char*, Shader> Shaders;
	std::unordered_map<const char*, Texture2D> Textures;


	Shader ResourceManager::LoadShader(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile, const char* name)
	{
		Shaders[name] = loadShaderFromFile(vShaderFile, fShaderFile, gShaderFile);
		return Shaders[name];
	}

	Shader ResourceManager::GetShader(const char* name)
	{
		return Shaders[name];
	}

	Texture2D ResourceManager::LoadTexture(const char* file, bool alpha, const char* name)
	{
		Textures[name] = loadTexture2DFromFile(file, alpha);
		return Textures[name];
	}

	Texture2D ResourceManager::GetTexture(const char* name)
	{
		return Textures[name];
	}

	void ResourceManager::Clear()
	{
		for (auto iter : Shaders)
			glDeleteProgram(iter.second.ID);

		for (auto iter : Textures)
			glDeleteProgram(iter.second.ID);
	}

	Shader ResourceManager::loadShaderFromFile(const char* vShaderPath, const char* fShaderPath, const char* gShaderPath)
	{
		std::string vertCode, fragCode, geoCode;

		try
		{
			std::ifstream vertShaderFile(vShaderPath);
			std::ifstream fragShaderFile(fShaderPath);
			std::stringstream vShaderStream, fShaderStream;

			vShaderStream << vertShaderFile.rdbuf();
			fShaderStream << fragShaderFile.rdbuf();

			vertShaderFile.close();
			fragShaderFile.close();

			vertCode = vShaderStream.str();
			fragCode = fShaderStream.str();

			if (gShaderPath != nullptr)
			{
				std::ifstream geoShaderFile(gShaderPath);
				std::stringstream gShaderStream;
				gShaderStream << geoShaderFile.rdbuf();
				geoShaderFile.close();
				geoCode = gShaderStream.str();
			}
		}
		catch (const std::exception& e)
		{
			ML_LOG_ERROR("ResourceManager: ", e.what());
		}

		const char* vShaderCode = vertCode.c_str();
		const char* fShaderCode = fragCode.c_str();
		const char* gShaderCode = geoCode.c_str();

		return Shader(vShaderCode, fShaderCode, gShaderPath != nullptr ? gShaderCode : nullptr);
	}

	Texture2D ResourceManager::loadTexture2DFromFile(const char* texturePath, bool alpha)
	{
		Texture2D texture;

		if (alpha)
		{
			texture.InternalFormat = GL_RGBA;
			texture.ImageFormat = GL_RGBA;
		}

		int width, height, nrChannels;
		unsigned char* data = stbi_load(texturePath, &width, &height, &nrChannels, 0);

		texture.Generate(width, height, data);

		stbi_image_free(data);
		return texture;
	}

}
