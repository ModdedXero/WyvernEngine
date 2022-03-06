#pragma once

#include <Merlin/Core/Math/Vector.h>

namespace Merlin
{
	struct RigidBody2D
	{
		Vector3 velocity;
		Vector3 force;

		float mass = 0.04f;
	};
}