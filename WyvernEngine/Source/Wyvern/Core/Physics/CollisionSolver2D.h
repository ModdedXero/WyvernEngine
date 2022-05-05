#pragma once

#include "Collision2D.h"

#include <vector>

namespace Wyvern
{
	class CollisionSolver2D
	{
	public:
		virtual void Solve(const std::vector<Ref<Collision2D>> collisions) {}
	};
}