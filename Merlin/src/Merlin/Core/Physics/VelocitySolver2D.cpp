#include "VelocitySolver2D.h"

namespace Merlin
{
	void VelocitySolver2D::Solve(RigidBody2D* rb, Timestep& ts, Transform* transform)
	{
		if (rb->bodyType != RigidBody2D::PhysicsBody::Dynamic) return;

		rb->velocity = (rb->velocity + rb->force * rb->GetInvMass() * ts.GetFixedDeltaTime()) - rb->velocity * rb->drag * rb->GetInvMass();
		transform->position = transform->position + rb->velocity * ts.GetFixedDeltaTime();

		rb->force = { 0, 0 };
	}
}