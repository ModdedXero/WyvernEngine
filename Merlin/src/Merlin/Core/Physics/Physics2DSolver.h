#pragma once

#include <Merlin/Core/Physics/Collider2D.h>

#include <vector>

namespace Merlin
{
	class Physics2DSolver
	{
	public:
		virtual void Solve(const std::vector<Collision2D> collisions) {}
	};
}