#pragma once

#include "PhysicsSolver2D.h"

namespace Merlin
{
	class VelocitySolver2D : public PhysicsSolver2D
	{
	public:
		void Solve(RigidBody2D* rb, Transform* transform) override;
	};
}