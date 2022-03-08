#pragma once

#include <Merlin/Core/Math/Vector.h>

namespace Merlin
{
	struct RigidBody2D
	{
		Vector2 velocity;
		Vector2 force;

		float mass = 1.0f;
		float invMass = 1.0f / mass;
		float friction = 0.03f;
		float bounce = 0.2f;

		bool isStatic = false;
	};
}