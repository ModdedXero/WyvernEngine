#include "wvpch.h"
#include "VelocitySolver2D.h"

namespace Wyvern
{
	void VelocitySolver2D::Solve(RigidBody2D* rb, Transform* transform)
	{
		if (rb->bodyType != RigidBody2D::PhysicsBody::Dynamic) return;

		rb->velocity = (rb->velocity + rb->force * rb->GetInvMass() * Timestep::GetFixedDeltaTime()) - rb->velocity * rb->drag * rb->GetInvMass();
		transform->position = transform->position + rb->velocity * Timestep::GetFixedDeltaTime();

		rb->force = { 0, 0 };
	}
}