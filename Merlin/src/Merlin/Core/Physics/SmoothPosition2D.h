#pragma once

#include <Merlin/Core/Base.h>
#include "CollisionSolver2D.h"

namespace Merlin
{
	class SmoothPosition2D : public CollisionSolver2D
	{
	public:
		void Solve(const std::vector<Ref<Collision2D>> collisions) override;
	};
}