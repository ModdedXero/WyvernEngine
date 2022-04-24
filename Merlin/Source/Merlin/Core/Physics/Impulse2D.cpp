#include "mlpch.h"
#include "Impulse2D.h"

#include <Merlin/Core/Components/RigidBody2D.h>

namespace Merlin
{
	void Impulse2D::Solve(const std::vector<Ref<Collision2D>> collisions)
	{
		for (Ref<Collision2D> collision : collisions)
		{
			RigidBody2D* rbA = collision->entityA->GetComponent<RigidBody2D>();
			RigidBody2D* rbB = collision->entityB->GetComponent<RigidBody2D>();

			float aInvMass = rbA->GetInvMass();
			float bInvMass = rbB->GetInvMass();

			if (aInvMass + bInvMass == 0) continue;

			Vector2 rv = rbB->velocity - rbA->velocity;

			float velN = Vector2::Dot(rv, collision->normal);

			if (velN > 0)
				continue;

			float e = fmin(rbA->bounce, rbB->bounce);

			float j = -(1 + e) * velN;
			j /= aInvMass + bInvMass;

			Vector2 impulse = collision->normal * j;
			rbA->velocity -= impulse * aInvMass;
			rbB->velocity += impulse * bInvMass;
		}
	}
}