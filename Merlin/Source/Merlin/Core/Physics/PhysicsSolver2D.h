#pragma once


#include <Merlin/Core/Timestep.h>
#include <Merlin/Core/Components/Transform.h>
#include <Merlin/Core/Components/RigidBody2D.h>

namespace Merlin
{
	class PhysicsSolver2D
	{
	public:
		virtual void Solve(RigidBody2D* rb, Transform* transform) {}
	};
}