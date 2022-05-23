#pragma once

#include "Collision2D.h"

#include <vector>

namespace Wyvern
{
	class CollisionSolver2D
	{
	public:
		virtual void Solve(std::vector<Collision2D> collisions) {}
	};
}