#pragma once

#include <Merlin/Core/Math/Vector.h>

namespace Merlin
{
	struct RigidBody2D
	{
		Vector2 velocity;
		Vector2 force;

		enum class PhysicsBody
		{
			Dynamic = 0,
			Kinematic = 1,
			Static = 2
		} bodyType = PhysicsBody::Dynamic;

		float mass = 1.0f;
		float invMass = 1.0f / mass;
		float friction = 0.05f;
		float bounce = 0.2f;
	};
}