#include "PushSolver2D.h"

namespace Merlin
{
	void PushSolver2D::Solve(RigidBody2D* rb, Timestep& ts, Transform* transform)
	{
		if (rb->isStatic) return;

		rb->velocity += (rb->force / rb->mass) * ts.GetDeltaTime() + -rb->velocity * ((1 / rb->mass) * rb->friction);

		transform->position += rb->velocity * ts.GetDeltaTime();
		rb->force = Vector3();
	}
}