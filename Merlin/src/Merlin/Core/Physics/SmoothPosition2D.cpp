#include "SmoothPosition2D.h"

#include "RigidBody2D.h"

namespace Merlin
{
	void SmoothPosition2D::Solve(const std::vector<Collision2D*> collisions)
	{
		for (Collision2D* collision : collisions)
		{
			RigidBody2D* rbA = collision->entityA->GetComponent<RigidBody2D>();
			RigidBody2D* rbB = collision->entityB->GetComponent<RigidBody2D>();

			float aMass = rbA->mass > 0 ? rbA->invMass : 0.0f;
			float bMass = rbB->mass > 0 ? rbB->invMass : 0.0f;

			const float percent = 0.2f;
			const float slop = 0.01f;

			Vector2 correction =
				collision->normal * fmax(collision->penetration - slop, 0.0f) /
				(aMass + bMass) * percent;

			if (!rbA->isStatic) collision->entityA->GetTransform()->position -= correction * aMass;
			if (!rbB->isStatic) collision->entityB->GetTransform()->position += correction * bMass;
		}
	}
}