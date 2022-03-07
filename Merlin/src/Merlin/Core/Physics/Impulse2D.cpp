#include "mlpch.h"
#include "Impulse2D.h"

#include <Merlin/Scene/Scene.h>
#include <Merlin/Core/Physics/RigidBody2D.h>

namespace Merlin
{
	void Impulse2D::Solve(const std::vector<Collision2D> collisions)
	{
		for (Collision2D collision : collisions)
		{
			RigidBody2D* rbA = Scene::GetComponent<RigidBody2D>(collision.entityA);
			RigidBody2D* rbB = Scene::GetComponent<RigidBody2D>(collision.entityB);

			Vector2 rv = rbB->velocity - rbA->velocity;

			float velAlongNormal = Vector2::Dot(rv, collision.normal);

			if (velAlongNormal > 0)
				return;

			float e = fmin(rbA->bounce, rbB->bounce);

			float j = -(1 + e) * velAlongNormal;
			//ML_LOG_INFO(-(1 + e) * velAlongNormal, " || ", velAlongNormal);
			j /= rbA->invMass + rbB->invMass;

			Vector2 impulse = collision.normal * j;
			rbA->velocity -= impulse * rbA->invMass;
			rbB->velocity += impulse * rbB->invMass;
		}
	}
}