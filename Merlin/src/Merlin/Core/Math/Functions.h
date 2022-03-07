#pragma once

#include <Merlin/Core/Math/Vector.h>

namespace Merlin
{
	class Functions
	{
	public:
		static Vector2 Clamp(Vector2& value, Vector2& min, Vector2& max)
		{
			if (value < min)
			{
				return min;
			}

			if (value > max)
			{
				return max;
			}

			return value;
		}
	};
}