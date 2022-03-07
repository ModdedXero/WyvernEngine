#pragma once

#include <Merlin/Core/Physics/Physics2DSolver.h>

namespace Merlin
{
	class SmoothPosition2D : public Physics2DSolver
	{
	public:
		void Solve(const std::vector<Collision2D> collisions) override;
	};
}