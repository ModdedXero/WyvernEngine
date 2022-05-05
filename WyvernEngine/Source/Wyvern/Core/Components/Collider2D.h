#pragma once

#include <Wyvern/Core/Math/Vector.h>
#include <Wyvern/Core/Scene/Component.h>

namespace Wyvern
{
	struct BoxCollider2D : public Component
	{
		Vector2 size = Vector2(0, 0);

		WV_SERIALIZE_COMPONENT(BoxCollider2D)
		WV_SERIALIZE_VARIABLE(Vector2, size)
		WV_SERIALIZE_COMPONENT_END
	};

	struct SphereCollider2D : public Component
	{
		float radius = 0.0f;

		WV_SERIALIZE_COMPONENT(SphereCollider2D)
		WV_SERIALIZE_VARIABLE(float, radius)
		WV_SERIALIZE_COMPONENT_END
	};
}