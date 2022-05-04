#pragma once

#include <Wyvern/Core/Math/Vector.h>
#include <Wyvern/Core/Scene/Component.h>

namespace Wyvern
{
	class Entity;

	struct BoxCollider2D : public Component
	{
		BoxCollider2D() {}
		~BoxCollider2D() {}

		Vector2 size = Vector2(0, 0);
	};

	struct SphereCollider2D : public Component
	{
		SphereCollider2D() {}
		~SphereCollider2D() {}

		float radius = 0.0f;
	};

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