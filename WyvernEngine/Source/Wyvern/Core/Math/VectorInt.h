#pragma once

namespace Wyvern
{
	struct Vector2;

	struct Vector2Int
	{
		int x = 0;
		int y = 0;

		Vector2Int()
		{
			x = 0;
			y = 0;
		}

		Vector2Int(int x, int y)
		{
			this->x = x;
			this->y = y;
		}
	};
}