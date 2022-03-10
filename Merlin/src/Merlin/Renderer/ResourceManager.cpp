#include "mlpch.h"
#include "ResourceManager.h"

#include <stb_image.h>

namespace Merlin::Renderer
{
	std::unordered_map<const char*, Shader> Shaders;
	std::unordered_map<const char*, Texture2D> Textures;
	std::unordered_map<const char*, SubTexture2D> SubTextures;

	Shader ResourceManager::LoadShader(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile, const char* name)
	{
		Shaders[name] = loadShaderFromFile(vShaderFile, fShaderFile, gShaderFile);
		Shaders[name].Use();
		Shaders[name].SetMatrix4("model", glm::mat4(1.0f));
		int samplers[32];
		for (int i = 0; i < 32; i++)
			samplers[i] = i;
		Shaders[name].SetIntArray("uTextures", 32, samplers);
		return Shaders[name];
	}

	Shader ResourceManager::GetShader(const char* name)
	{
		return Shaders[name];
	}

	Texture2D ResourceManager::LoadTexture(const char* file, bool alpha, bool pixel, const char* name)
	{
		Textures[name] = loadTexture2DFromFile(file, alpha, pixel);
		return Textures[name];
	}

	Texture2D ResourceManager::GetTexture(const char* name)
	{
		return Textures[name];
	}

	SubTexture2D ResourceManager::LoadSubTexture(const char* name, const char* textureName, const Vector2& coords, const Vector2& spriteSize)
	{
		SubTextures[name] = SubTexture2D::CreateFromCoords(GetTexture(textureName), coords, spriteSize);
		return SubTextures[name];
	}

	SubTexture2D ResourceManager::GetSubTexture(const char* name)
	{
		return SubTextures[name];
	}

	void ResourceManager::Clear()
	{
		for (auto &iter : Shaders)
			glDeleteProgram(iter.second.ID);

		for (auto &iter : Textures)
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

	Texture2D ResourceManager::loadTexture2DFromFile(const char* texturePath, bool alpha, bool pixel)
	{
		Texture2D texture;

		if (alpha)
		{
			texture.InternalFormat = GL_RGBA;
			texture.ImageFormat = GL_RGBA;
		}

		if (pixel)
		{
			texture.FilterMin = GL_NEAREST;
			texture.FilterMax = GL_NEAREST;
		}

		int width, height, nrChannels;
		unsigned char* data = stbi_load(texturePath, &width, &height, &nrChannels, 0);

		texture.Generate(width, height, data);

		stbi_image_free(data);
		return texture;
	}

}
