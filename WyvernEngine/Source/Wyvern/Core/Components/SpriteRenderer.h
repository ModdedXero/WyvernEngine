#pragma once

#include <Wyvern/Core/Graphics/Material.h>
#include <Wyvern/Core/Graphics/Sprite.h>
#include <Wyvern/Core/AssetManager.h>
#include <Wyvern/Core/Scene/Component.h>

namespace Wyvern
{
	struct SpriteRenderer : public Component
	{
		SpriteRenderer() {}
		~SpriteRenderer() {}

		Ref<Sprite> sprite;
		Ref<Material> material = AssetManager::GetDefaultMaterial();

		Vector4 color = { 1.0f,1.0f,1.0f,1.0f };
		uint32_t zIndex = 0; // Not implemented yet

		WV_SERIALIZE_COMPONENT(SpriteRenderer)
		WV_SERIALIZE_ASSET(Sprite, sprite)
		WV_SERIALIZE_VARIABLE(Vector4, color)
		WV_SERIALIZE_COMPONENT_END
	};
}