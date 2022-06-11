#pragma once

#include <Wyvern/Core/Graphics/Material.h>
#include <Wyvern/Core/Graphics/Sprite.h>
#include <Wyvern/Core/AssetManager.h>
#include <Wyvern/Core/Scene/NativeScriptComponent.h>

namespace Wyvern
{
	struct SpriteRenderer : public NativeScriptComponent<SpriteRenderer>
	{
		SpriteRenderer() {}
		~SpriteRenderer() {}

		Ref<Sprite> sprite;
		Ref<Material> material = AssetManager::GetDefaultMaterial();

		Vector4 color = { 1.0f,1.0f,1.0f,1.0f };
		uint32_t zIndex = 0; // Not implemented yet

		virtual void DrawEditor() override;
	};
}