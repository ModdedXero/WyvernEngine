#pragma once

#include <Wyvern/Core/Scene/Component.h>
#include <Wyvern/Core/Graphics/Mesh.h>

namespace Wyvern
{
	struct MeshFilter : public Component<MeshFilter>
	{
		Mesh mesh;

		virtual void DrawEditor() override;
	};
}