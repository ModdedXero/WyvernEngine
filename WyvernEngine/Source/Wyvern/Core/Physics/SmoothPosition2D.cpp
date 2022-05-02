#include "wvpch.h"
#include "SmoothPosition2D.h"

#include <Wyvern/Core/Components/RigidBody2D.h>
#include <Wyvern/Core/Components/Transform.h>
#include <Wyvern/Core/Scene/Entity.h>

namespace Wyvern
{
	void SmoothPosition2D::Solve(const std::vector<Ref<Collision2D>> collisions)
	{
		for (Ref<Collision2D> collision : collisions)
		{
			RigidBody2D* rbA = Scene::GetComponent<RigidBody2D>(collision->entityA);
			RigidBody2D* rbB = Scene::GetComponent<RigidBody2D>(collision->entityB);

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