#pragma once

#include <Merlin/Core/Graphics/Material.h>
#include <Merlin/Core/Graphics/Sprite.h>
#include <Merlin/Core/AssetManager.h>
#include <Merlin/Core/Scene/Component.h>

namespace Merlin
{
	struct SpriteRenderer : public Component
	{
		SpriteRenderer() {}
		~SpriteRenderer() {}

		Ref<Sprite> sprite;
		Ref<Material> material = AssetManager::GetDefaultMaterial();

		Vector4 color = { 1.0f,1.0f,1.0f,1.0f };
		uint32_t zIndex = 0;
	};
}