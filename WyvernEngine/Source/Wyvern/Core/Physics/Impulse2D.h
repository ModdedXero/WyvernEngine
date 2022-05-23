#pragma once

#include <Wyvern/Core/Physics/CollisionSolver2D.h>

namespace Wyvern
{
	class Impulse2D : public CollisionSolver2D
	{
		void Solve(std::vector<Collision2D> collisions) override;
	};
}