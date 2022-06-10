#pragma once

#include <Wyvern/Core/Scene/Component.h>
#include <Wyvern/Core/Graphics/Material.h>
#include <Wyvern/Core/Components/MeshFilter.h>
#include <Wyvern/Core/AssetManager.h>

namespace Wyvern
{
	struct MeshRenderer : public Component
	{
	public:
		std::vector<Ref<Material>> materials = std::vector<Ref<Material>>{ AssetManager::GetDefaultMaterial() };

		WV_SERIALIZE_COMPONENT(MeshRenderer)
		WV_SERIALIZE_VARIABLE(std::vector<Ref<Material>>, materials)
		WV_SERIALIZE_COMPONENT_END
	};
}