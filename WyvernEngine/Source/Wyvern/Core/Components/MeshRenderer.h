#pragma once

#include <Wyvern/Core/Scene/NativeScriptComponent.h>
#include <Wyvern/Core/Graphics/Material.h>
#include <Wyvern/Core/Components/MeshFilter.h>
#include <Wyvern/Core/AssetManager.h>

namespace Wyvern
{
	struct MeshRenderer : public NativeScriptComponent<MeshRenderer>
	{
	public:
		std::vector<Ref<Material>> materials = std::vector<Ref<Material>>{ AssetManager::GetDefaultMaterial() };

		virtual void DrawEditor() override;
	};
}