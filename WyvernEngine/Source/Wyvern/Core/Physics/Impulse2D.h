#pragma once

#include <Wyvern/Core/Physics/CollisionSolver2D.h>

namespace Wyvern
{
	class Impulse2D : public CollisionSolver2D
	{
		void Solve(const std::vector<Ref<Collision2D>> collisions) override;
	};
}