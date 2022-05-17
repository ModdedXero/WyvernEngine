#include "wvpch.h"
#include "Vector.h"

#include "VectorInt.h"

namespace Wyvern
{
	Vector2::operator Vector2Int() const
	{
		return Vector2Int(x, y);
	}
}