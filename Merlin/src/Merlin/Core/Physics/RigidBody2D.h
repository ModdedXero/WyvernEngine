#pragma once

#include <Merlin/Core/Math/Vector.h>

namespace Merlin
{
	struct RigidBody2D
	{
		Vector2 velocity;
		Vector2 force;

		float mass = 0.04f;
		float invMass = 1 / mass;
		float bounce = 0.3f;

		bool isStatic = false;
	};
}