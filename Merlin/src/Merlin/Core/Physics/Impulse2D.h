#pragma once

#include <Merlin/Core/Physics/Physics2DSolver.h>

#include <vector>

namespace Merlin
{
	class Impulse2D : public Physics2DSolver
	{
		void Solve(const std::vector<Collision2D> collisions) override;
	};
}