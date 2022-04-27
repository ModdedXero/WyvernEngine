#pragma once

#include <Wyvern/Core/Math/Vector.h>

namespace Wyvern
{
	class Mathf
	{
	public:
		static Vector2 Clamp(Vector2 value, Vector2 min, Vector2 max)
		{
			if (value.x < min.x) value.x = min.x;
			if (value.x > max.x) value.x = max.x;

			if (value.y < min.y) value.y = min.y;
			if (value.y > max.y) value.y = max.y;

			return value;
		}
	};
}