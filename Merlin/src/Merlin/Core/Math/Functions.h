#pragma once

#include <Merlin/Core/Math/Vector.h>

namespace Merlin
{
	class Functions
	{
	public:
		static Vector2 Clamp(Vector2 value, Vector2 min, Vector2 max)
		{
			if (value.Length() < min.Length())
			{
				return min;
			}

			if (value.Length() > max.Length())
			{
				return max;
			}

			return value;
		}
	};
}