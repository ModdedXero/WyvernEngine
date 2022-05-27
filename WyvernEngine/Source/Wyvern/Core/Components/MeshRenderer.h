#pragma once

#include <Wyvern/Core/Scene/Component.h>
#include <Wyvern/Core/Graphics/MeshFilter.h>
#include <Wyvern/Core/Graphics/Material.h>

namespace Wyvern
{
	struct MeshRenderer : public Component
	{
	public:
		MeshFilter mesh;
		Ref<Material> material = AssetManager::GetDefaultMaterial();

		WV_SERIALIZE_COMPONENT(MeshRenderer)
		WV_SERIALIZE_VARIABLE(MeshFilter, mesh)
		WV_SERIALIZE_COMPONENT_END
	};
}