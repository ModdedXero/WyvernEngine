#pragma once

#include <Wyvern/Core/Math/Vector.h>

namespace Wyvern
{
	class Entity;

	struct Collision2D
	{
		Collision2D(Entity* a, Entity* b, Vector2 normal, float penetration)
		{
			this->entA = a;
			this->entB = b;
			this->normal = normal;
			this->penetration = penetration;
		}

		Entity* entA;
		Entity* entB;
		Vector2 normal;
		float penetration;
	};
}