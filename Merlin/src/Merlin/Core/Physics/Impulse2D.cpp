#include "mlpch.h"
#include "Impulse2D.h"

#include "RigidBody2D.h"

namespace Merlin
{
	void Impulse2D::Solve(const std::vector<Collision2D*> collisions)
	{
		for (Collision2D* collision : collisions)
		{
			RigidBody2D* rbA = collision->entityA->GetComponent<RigidBody2D>();
			RigidBody2D* rbB = collision->entityB->GetComponent<RigidBody2D>();

			Vector2 rv = rbB->velocity - rbA->velocity;

			ML_LOG_INFO(collision->normal);
			float velN = Vector2::Dot(rv, collision->normal);

			if (velN > 0)
				return;

			float e = fmin(rbA->bounce, rbB->bounce);

			float j = -(1 + e) * velN;
			j /= 1 / rbA->mass + 1 / rbB->mass;

			Vector2 impulse = collision->normal * j;
			rbA->velocity -= impulse * (1 / rbA->mass);
			rbB->velocity += impulse * (1 / rbB->mass);
		}
	}
}