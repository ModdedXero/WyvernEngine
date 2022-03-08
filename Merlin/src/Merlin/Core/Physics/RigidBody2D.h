#pragma once

#include <Merlin/Core/Math/Vector.h>

namespace Merlin
{
	struct RigidBody2D
	{
		Vector2 velocity;
		Vector2 force;

		float mass = 1.0f;
		float friction = 0.05f;
		float bounce = 0.4f;

		bool isStatic = false;
	};
}