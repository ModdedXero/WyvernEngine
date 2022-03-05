#pragma once

#include <Merlin/Core/Math/Vector.h>

namespace Merlin
{
	struct RigidBody2D
	{
		Vector3 velocity;
		float mass;
	};
}