#pragma once

#include <Wyvern/Core/Base.h>

#include <Wyvern/Core/Graphics/Shader.h>
#include <Wyvern/Core/Graphics/Texture2D.h>
#include <Wyvern/Core/Graphics/Sprite.h>
#include <Wyvern/Core/Graphics/Material.h>

#include <Wyvern/Core/Math/Vector.h>

#include <glad.h>

namespace Wyvern
{
	class AssetManager
	{
	public:
		static Ref<Shader> LoadShader(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile, const char* name);
		static Ref<Shader> GetShader(const char* name);

		static Ref<Texture2D> LoadTexture(Ref<Texture2D> texture, const char* name);
		static Ref<Texture2D> GetTexture(const char* name);

		static Ref<Sprite> LoadSprite(const char* name, const char* textureName, const Vector2& coords, const Vector2& tileSize, const Vector2& spriteSize);
		static Ref<Sprite> GetSprite(const char* name);

		static Ref<Material> LoadMaterial(const char* shader, const char* name);
		static Ref<Material> GetMaterial(const char* name);

		static Ref<Material> GetDefaultMaterial();

		static void Clear();
	private:
		AssetManager() {}

		static Ref<Shader> loadShaderFromFile(const char* vShaderPath, const char* fShaderPath, const char* gShaderPath = nullptr);
	};
}