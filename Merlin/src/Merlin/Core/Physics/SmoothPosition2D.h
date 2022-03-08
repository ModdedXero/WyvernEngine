#pragma once

#include "CollisionSolver2D.h"

namespace Merlin
{
	class SmoothPosition2D : public CollisionSolver2D
	{
	public:
		void Solve(const std::vector<Collision2D*> collisions) override;
	};
}