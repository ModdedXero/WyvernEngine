#pragma once

#include <Wyvern/Core/Base.h>

#include <Wyvern/Core/Graphics/Shader.h>
#include <Wyvern/Core/Graphics/Texture2D.h>
#include <Wyvern/Core/Graphics/Sprite.h>
#include <Wyvern/Core/Graphics/Material.h>

#include <Wyvern/Core/Math/Vector.h>
#include <Wyvern/Utils/FileSystem.h>

#include <glad.h>

namespace Wyvern
{
	class AssetManager
	{
	public:
		static Ref<Shader> LoadShader(Tools::FileSystem vShaderFile, Tools::FileSystem fShaderFile, Tools::FileSystem gShaderFile, std::string name);
		static Ref<Shader> GetShader(std::string name);

		static Ref<Texture2D> LoadTexture(Ref<Texture2D> texture, std::string name);
		static Ref<Texture2D> GetTexture(std::string name);

		static Ref<Sprite> LoadSprite(std::string name, std::string textureName, const Vector2& coords, const Vector2& tileSize, const Vector2& spriteSize);
		static Ref<Sprite> GetSprite(std::string name);

		static Ref<Material> LoadMaterial(std::string shader, std::string name);
		static Ref<Material> GetMaterial(std::string name);

		static Ref<Material> GetDefaultMaterial();

		static void Clear();
	private:
		AssetManager() {}

		static Ref<Shader> loadShaderFromFile(std::string vShaderPath, std::string fShaderPath, std::string gShaderPath = std::string());
	};
}