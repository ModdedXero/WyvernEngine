#pragma once

#include <Wyvern/Core/Scene/Component.h>
#include <Wyvern/Core/Graphics/Mesh.h>

namespace Wyvern
{
	struct MeshFilter : public Component
	{
		Mesh mesh;

		WV_SERIALIZE_COMPONENT(MeshFilter)
		WV_SERIALIZE_VARIABLE(Mesh, mesh)
		WV_SERIALIZE_COMPONENT_END
	};
}