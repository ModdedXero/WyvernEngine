#pragma once

#include <Merlin/Core/Math/Vector.h>
#include <Merlin/Core/Scene/Entity.h>

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
		Collision2D(Entity* a, Entity* b, Vector2 normal, float penetration)
		{
			this->entityA = a;
			this->entityB = b;
			this->normal = normal;
			this->penetration = penetration;
		}

		Entity* entityA;
		Entity* entityB;
		Vector2 normal;
		float penetration;
	};
}