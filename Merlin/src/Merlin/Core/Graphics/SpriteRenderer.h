#pragma once

#include "Material.h"
#include "Sprite.h"

#include <Merlin/Core/Scene/Component.h>

namespace Merlin
{
	struct SpriteRenderer : public Component
	{
		SpriteRenderer() {}
		~SpriteRenderer() {}

		Sprite* sprite = nullptr;
		Material* material = nullptr;

		Vector4 color = { 1.0f,1.0f,1.0f,1.0f };
		uint32_t zIndex = 0;
	};
}