#pragma once

#include <Merlin/Core/Physics/CollisionSolver2D.h>

namespace Merlin
{
	class Impulse2D : public CollisionSolver2D
	{
		void Solve(const std::vector<Ref<Collision2D>> collisions) override;
	};
}