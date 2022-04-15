#include "SmoothPosition2D.h"

#include "RigidBody2D.h"

namespace Merlin
{
	void SmoothPosition2D::Solve(const std::vector<Ref<Collision2D>> collisions)
	{
		for (Ref<Collision2D> collision : collisions)
		{
			RigidBody2D* rbA = collision->entityA->GetComponent<RigidBody2D>();
			RigidBody2D* rbB = collision->entityB->GetComponent<RigidBody2D>();

			float aMass = rbA->GetInvMass();
			float bMass = rbB->GetInvMass();

			const float percent = 0.5f;
			const float slop = 0.01f;

			float collectiveMass = aMass + bMass;

			Vector2 correction =
				collectiveMass > 0 ?
				collision->normal * fmax(collision->penetration - slop, 0.0f) /
				(aMass + bMass) * percent :
				collision->normal * fmax(collision->penetration - slop, 0.0f) / percent;

			if (rbA->bodyType != RigidBody2D::PhysicsBody::Static) collision->entityA->GetTransform()->position -= correction * aMass;
			if (rbB->bodyType != RigidBody2D::PhysicsBody::Static) collision->entityB->GetTransform()->position += correction * bMass;
		}
	}
}