#pragma once

#include <glad.h>

#include "Merlin/Renderer/Shader.h"
#include "Merlin/Renderer/Texture2D.h"

namespace Merlin
{
	class ResourceManager
	{
	public:
		static Shader LoadShader(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile, const char* name);
		static Shader GetShader(const char* name);

		static Texture2D LoadTexture(const char* file, bool alpha, bool pixel, const char* name);
		static Texture2D GetTexture(const char* name);

		static void Clear();
	private:
		ResourceManager() {}

		static Shader loadShaderFromFile(const char* vShaderPath, const char* fShaderPath, const char* gShaderPath = nullptr);
		static Texture2D loadTexture2DFromFile(const char* texturePath, bool alpha, bool pixel);
	};
}