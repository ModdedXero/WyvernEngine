#pragma once

#include <Merlin/Core/Graphics/Shader.h>
#include <Merlin/Core/Graphics/Texture2D.h>
#include <Merlin/Core/Graphics/Sprite.h>

#include <Merlin/Core/Math/Vector.h>

#include <glad.h>

namespace Merlin
{
	class ResourceManager
	{
	public:
		static Shader* LoadShader(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile, const char* name);
		static Shader* GetShader(const char* name);

		static Texture2D* LoadTexture(const char* file, bool alpha, bool pixel, const char* name);
		static Texture2D* GetTexture(const char* name);

		static Sprite* LoadSubTexture(const char* name, const char* textureName, const Vector2& coords, const Vector2& tileSize, const Vector2& spriteSize);
		static Sprite* GetSubTexture(const char* name);

		static std::unordered_map<const char*, Shader*> GetShaders();
		static std::unordered_map<const char*, Texture2D*> GetTextures();
		static std::unordered_map<const char*, Sprite*> GetSubTextures();

		static void Clear();
	private:
		ResourceManager() {}

		static Shader* loadShaderFromFile(const char* vShaderPath, const char* fShaderPath, const char* gShaderPath = nullptr);
		static Texture2D* loadTexture2DFromFile(const char* texturePath, bool alpha, bool pixel);
	};
}