#pragma once

#include <Merlin/Core/Math/Vector.h>
#include <Merlin/Scene/Transform.h>
#include <Merlin/Scene/Tag.h>

namespace Merlin
{
	struct BoxCollider2D
	{
		Vector2 size;
		float distance;
	};

	struct SphereCollider2D
	{
		Vector2 center;
		float radius;
	};

	struct Collision2D
	{
		unsigned long long entityA;
		unsigned long long entityB;
		Vector2 normal;
		float penetration;
	};
}