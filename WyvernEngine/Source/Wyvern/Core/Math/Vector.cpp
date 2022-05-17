#include "wvpch.h"
#include "Vector.h"

#include "VectorInt.h"

namespace Wyvern
{
	Vector2::operator Vector3() const
	{
		return Vector3(x, y, 0);
	}

	Vector2::operator Vector4() const
	{
		return Vector4(x, y, 0, 0);
	}

	Vector2::operator Vector2Int() const
	{
		return Vector2Int(x, y);
	}

	Vector2::operator Vector3Int() const
	{
		return Vector3Int(x, y, 0);
	}

	Vector2::operator Vector4Int() const
	{
		return Vector4Int(x, y, 0, 0);
	}

	Vector3::operator Vector2() const
	{
		return Vector2(x, y);
	}

	Vector3::operator Vector4() const
	{
		return Vector4(x, y, z, 0);
	}

	Vector3::operator Vector2Int() const
	{
		return Vector2Int(x, y);
	}

	Vector3::operator Vector3Int() const
	{
		return Vector3Int(x, y, 0);
	}

	Vector3::operator Vector4Int() const
	{
		return Vector4Int(x, y, z, 0);
	}

	Vector3::operator glm::vec3() const
	{
		return glm::vec3(x, y, z);
	}

	Vector4::operator Vector2() const
	{
		return Vector2(x, y);
	}

	Vector4::operator Vector3() const
	{
		return Vector3(x, y, z);
	}

	Vector4::operator Vector2Int() const
	{
		return Vector2Int(x, y);
	}

	Vector4::operator Vector3Int() const
	{
		return Vector3Int(x, y, z);
	}

	Vector4::operator Vector4Int() const
	{
		return Vector4Int(x, y, z, w);
	}
}