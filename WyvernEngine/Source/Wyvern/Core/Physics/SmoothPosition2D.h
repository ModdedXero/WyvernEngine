#pragma once

#include <Wyvern/Core/Base.h>
#include "CollisionSolver2D.h"

namespace Wyvern
{
	class SmoothPosition2D : public CollisionSolver2D
	{
	public:
		void Solve(std::vector<Collision2D> collisions) override;
	};
}