#pragma once

#include <Merlin/Core/Timestep.h>
#include <Merlin/Core/Physics/RigidBody2D.h>
#include <Merlin/Scene/Transform.h>

namespace Merlin
{
	class PhysicsSolver2D
	{
	public:
		virtual void Solve(RigidBody2D* rb, Timestep& ts, Transform* transform) {}
	};
}