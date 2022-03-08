#pragma once

#include <Merlin/Core/Physics/Collider2D.h>

#include <vector>

namespace Merlin
{
	class CollisionSolver2D
	{
	public:
		virtual void Solve(const std::vector<Collision2D> collisions) {}
	};
}