#include "wvpch.h"
#include "SmoothPosition2D.h"

#include <Wyvern/Core/Components/RigidBody2D.h>
#include <Wyvern/Core/Components/Transform.h>
#include <Wyvern/Core/Scene/Entity.h>

namespace Wyvern
{
	void SmoothPosition2D::Solve(std::vector<Collision2D> collisions)
	{
		for (Collision2D& collision : collisions)
		{
			RigidBody2D* rbA = Scene::GetComponent<RigidBody2D>(collision.entA);
			RigidBody2D* rbB = Scene::GetComponent<RigidBody2D>(collision.entB);

			float aMass = rbA->GetInvMass();
			float bMass = rbB->GetInvMass();

			const float percent = 0.5f;
			const float slop = 0.01f;

			float collectiveMass = aMass + bMass;

			Vector2 correction =
				collectiveMass > 0 ?
				collision.normal * fmax(collision.penetration - slop, 0.0f) /
				(aMass + bMass) * percent :
				collision.normal * fmax(collision.penetration - slop, 0.0f) / percent;

			if (rbA->bodyType != PhysicsBody::Static) collision.entA.GetTransform()->position -= correction * aMass;
			if (rbB->bodyType != PhysicsBody::Static) collision.entB.GetTransform()->position += correction * bMass;
		}
	}
}