#pragma once


#include <Wyvern/Core/Timestep.h>
#include <Wyvern/Core/Components/Transform.h>
#include <Wyvern/Core/Components/RigidBody2D.h>

namespace Wyvern
{
	class PhysicsSolver2D
	{
	public:
		virtual void Solve(RigidBody2D* rb, Transform* transform) {}
	};
}