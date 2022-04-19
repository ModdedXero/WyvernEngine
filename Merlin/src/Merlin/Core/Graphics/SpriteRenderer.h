#pragma once

#include "Material.h"
#include "Sprite.h"

#include <Merlin/Core/ResourceManager.h>
#include <Merlin/Core/Scene/Component.h>

namespace Merlin
{
	struct SpriteRenderer : public Component
	{
		SpriteRenderer() {}
		~SpriteRenderer() {}

		Ref<Sprite> sprite;
		Ref<Material> material = ResourceManager::GetDefaultMaterial();

		Vector4 color = { 1.0f,1.0f,1.0f,1.0f };
		uint32_t zIndex = 0;
	};
}