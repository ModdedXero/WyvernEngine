#pragma once

#include <Merlin/Core/Base.h>

#include <Merlin/Core/Graphics/Shader.h>
#include <Merlin/Core/Graphics/Texture2D.h>
#include <Merlin/Core/Graphics/Sprite.h>
#include <Merlin/Core/Graphics/Material.h>

#include <Merlin/Core/Math/Vector.h>

#include <glad.h>

namespace Merlin
{
	class ResourceManager
	{
	public:
		static Ref<Shader> LoadShader(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile, const char* name);
		static Ref<Shader> GetShader(const char* name);

		static Ref<Texture2D> LoadTexture(const char* file, bool alpha, bool pixel, const char* name);
		static Ref<Texture2D> GetTexture(const char* name);

		static Ref<Sprite> LoadSprite(const char* name, const char* textureName, const Vector2& coords, const Vector2& tileSize, const Vector2& spriteSize);
		static Ref<Sprite> GetSprite(const char* name);

		static Ref<Material> LoadMaterial(const char* shader, const char* name);
		static Ref<Material> GetMaterial(const char* name);

		static void Clear();
	private:
		ResourceManager() {}

		static Ref<Shader> loadShaderFromFile(const char* vShaderPath, const char* fShaderPath, const char* gShaderPath = nullptr);
		static Ref<Texture2D> loadTexture2DFromFile(const char* texturePath, bool alpha, bool pixel);
	};
}