#pragma once

#include <Merlin/Core/Math/Vector.h>
#include <Merlin/Scene/Entity.h>

namespace Merlin
{
	class Entity;

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
		Entity* entityA;
		Entity* entityB;
		Vector2 normal;
		float penetration;
	};
}