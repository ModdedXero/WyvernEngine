#pragma once

#include <Wyvern/Core/Scene/NativeScriptComponent.h>
#include <Wyvern/Core/Graphics/Mesh.h>

namespace Wyvern
{
	struct MeshFilter : public NativeScriptComponent<MeshFilter>
	{
		Mesh mesh;

		virtual void DrawEditor() override;
	};
}