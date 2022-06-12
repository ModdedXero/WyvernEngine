#pragma once

#include <Wyvern/Core/Scene/Component.h>
#include <Wyvern/Core/Graphics/Material.h>
#include <Wyvern/Core/Components/MeshFilter.h>
#include <Wyvern/Core/AssetManager.h>

namespace Wyvern
{
	struct MeshRenderer : public Component<MeshRenderer>
	{
	public:
		std::vector<Ref<Material>> materials = std::vector<Ref<Material>>{ AssetManager::GetDefaultMaterial() };

		virtual void DrawEditor() override;
	};
}