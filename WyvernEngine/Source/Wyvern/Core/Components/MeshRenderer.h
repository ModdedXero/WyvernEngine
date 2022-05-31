#pragma once

#include <Wyvern/Core/Scene/Component.h>
#include <Wyvern/Core/Graphics/Material.h>
#include <Wyvern/Core/Components/MeshFilter.h>

namespace Wyvern
{
	struct MeshRenderer : public Component
	{
	public:
		Ref<Material> material = AssetManager::GetDefaultMaterial();

		WV_SERIALIZE_COMPONENT(MeshRenderer)
		WV_SERIALIZE_COMPONENT_END
	};
}