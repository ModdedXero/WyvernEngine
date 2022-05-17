#include "wvpch.h"
#include "VectorInt.h"

#include "Vector.h"

namespace Wyvern
{
	Vector2Int::operator Vector2() const
	{
		return Vector2(x, y);
	}

	Vector2Int::operator Vector3() const
	{
		return Vector3(x, y, 0);
	}

	Vector2Int::operator Vector4() const
	{
		return Vector4(x, y, 0, 0);
	}

	Vector2Int::operator Vector3Int() const
	{
		return Vector3Int(x, y, 0);
	}

	Vector2Int::operator Vector4Int() const
	{
		return Vector4Int(x, y, 0, 0);
	}

	Vector3Int::operator Vector2() const
	{
		return Vector2(x, y);
	}

	Vector3Int::operator Vector3() const
	{
		return Vector3(x, y, z);
	}

	Vector3Int::operator Vector4() const
	{
		return Vector4(x, y, z, 0);
	}

	Vector3Int::operator Vector2Int() const
	{
		return Vector2Int(x, y);
	}

	Vector3Int::operator Vector4Int() const
	{
		return Vector4Int(x, y, z, 0);
	}

	Vector4Int::operator Vector2() const
	{
		return Vector2(x, y);
	}

	Vector4Int::operator Vector3() const
	{
		return Vector3(x, y, z);
	}

	Vector4Int::operator Vector4() const
	{
		return Vector4(x, y, z, w);
	}

	Vector4Int::operator Vector2Int() const
	{
		return Vector2Int(x, y);
	}

	Vector4Int::operator Vector3Int() const
	{
		return Vector3Int(x, y, z);
	}
}