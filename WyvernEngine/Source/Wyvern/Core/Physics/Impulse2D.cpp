#include "wvpch.h"
#include "Impulse2D.h"

#include <Wyvern/Core/Components/RigidBody2D.h>
#include <Wyvern/Core/Scene/Entity.h>
#include <Wyvern/Core/Scene/Scene.h>

namespace Wyvern
{
	void Impulse2D::Solve(std::vector<Collision2D> collisions)
	{
		for (Collision2D& collision : collisions)
		{
			RigidBody2D* rbA = Scene::GetComponent<RigidBody2D>(collision.entA);
			RigidBody2D* rbB = Scene::GetComponent<RigidBody2D>(collision.entB);

			float aInvMass = rbA->GetInvMass();
			float bInvMass = rbB->GetInvMass();

			if (aInvMass + bInvMass == 0) continue;

			Vector2 rv = rbB->velocity - rbA->velocity;

			float velN = Vector2::Dot(rv, collision.normal);

			if (velN > 0)
				continue;

			float e = fmin(rbA->bounce, rbB->bounce);

			float j = -(1 + e) * velN;
			j /= aInvMass + bInvMass;

			Vector2 impulse = collision.normal * j;
			rbA->velocity -= impulse * aInvMass;
			rbB->velocity += impulse * bInvMass;
		}
	}
}