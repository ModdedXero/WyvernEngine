#pragma once

#include <iostream>

namespace Wyvern
{
	struct Vector2;
	struct Vector3;
	struct Vector4;

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

		// Functions

		Vector2Int Normalize() const
		{
			return *this / Length();
		}

		int Length() const
		{
			return (int)sqrt(Dot(*this, *this));
		}

		static int Dot(const Vector2Int& lhs, const Vector2Int& rhs)
		{
			return lhs.x * rhs.x + lhs.y * rhs.y;
		}

		// Vector2Int Operators

		Vector2Int operator -() const
		{
			return *this * -1;
		}

		void operator += (const Vector2Int& rhs)
		{
			x += rhs.x;
			y += rhs.y;
		}

		void operator -=(const Vector2Int& rhs)
		{
			x -= rhs.x;
			y -= rhs.x;
		}

		void operator *=(const Vector2Int& rhs)
		{
			x *= rhs.x;
			y *= rhs.y;
		}

		void operator /=(const Vector2Int& rhs)
		{
			x /= rhs.x;
			y /= rhs.y;
		}

		Vector2Int operator +(const Vector2Int& rhs) const
		{
			return Vector2Int(x + rhs.x, y + rhs.y);
		}

		Vector2Int operator -(const Vector2Int& rhs) const
		{
			return Vector2Int(x - rhs.x, y - rhs.y);
		}

		Vector2Int operator *(const Vector2Int& rhs) const
		{
			return Vector2Int(x * rhs.x, y * rhs.y);
		}

		Vector2Int operator /(const Vector2Int& rhs) const
		{
			return Vector2Int(x / rhs.x, y / rhs.y);
		}

		bool operator ==(const Vector2Int& rhs) const
		{
			return x == rhs.x && y == rhs.y;
		}

		bool operator !=(const Vector2Int& rhs) const
		{
			return x != rhs.x || y != rhs.y;
		}

		bool operator >=(const Vector2Int& rhs) const
		{
			return Length() >= rhs.Length();
		}

		bool operator <=(const Vector2Int& rhs) const
		{
			return Length() <= rhs.Length();
		}

		bool operator >(const Vector2Int& rhs) const
		{
			return Length() > rhs.Length();
		}

		bool operator <(const Vector2Int& rhs) const
		{
			return Length() < rhs.Length();
		}

		// Int Operators

		void operator += (const int& rhs)
		{
			x += rhs;
			y += rhs;
		}

		void operator -=(const int& rhs)
		{
			x -= rhs;
			y -= rhs;
		}

		void operator *=(const int& rhs)
		{
			x *= rhs;
			y *= rhs;
		}

		void operator /=(const int& rhs)
		{
			x /= rhs;
			y /= rhs;
		}

		Vector2Int operator +(const int& rhs) const
		{
			return Vector2Int(x + rhs, y + rhs);
		}

		Vector2Int operator -(const int& rhs) const
		{
			return Vector2Int(x - rhs, y - rhs);
		}

		Vector2Int operator *(const int& rhs) const
		{
			return Vector2Int(x * rhs, y * rhs);
		}

		Vector2Int operator /(const int& rhs) const
		{
			return Vector2Int(x / rhs, y / rhs);
		}

		bool operator ==(const int& rhs) const
		{
			return Length() == rhs;
		}

		bool operator !=(const int& rhs) const
		{
			return Length() != rhs;
		}

		bool operator >=(const int& rhs) const
		{
			return Length() >= rhs;
		}

		bool operator <=(const int& rhs) const
		{
			return Length() <= rhs;
		}

		bool operator >(const int& rhs) const
		{
			return Length() > rhs;
		}

		bool operator <(const int& rhs) const
		{
			return Length() < rhs;
		}

		// Conversions

		operator Vector2() const;
		operator Vector3() const;
		operator Vector4() const;

		operator Vector3Int() const;
		operator Vector4Int() const;
	};

	struct Vector3Int
	{
		int x = 0;
		int y = 0;
		int z = 0;

		Vector3Int()
		{
			x = 0;
			y = 0;
			z = 0;
		}

		Vector3Int(int x, int y, int z)
		{
			this->x = x;
			this->y = y;
			this->z = z;
		}

		// Functions

		Vector3Int Normalize() const
		{
			return *this / Length();
		}

		int Length() const
		{
			return (int)sqrt(Dot(*this, *this));
		}

		static int Dot(const Vector3Int& lhs, const Vector3Int& rhs)
		{
			return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
		}

		// Vector3Int Operators

		void operator += (const Vector3Int& rhs)
		{
			x += rhs.x;
			y += rhs.y;
		}

		void operator -=(const Vector3Int& rhs)
		{
			x -= rhs.x;
			y -= rhs.x;
		}

		void operator *=(const Vector3Int& rhs)
		{
			x *= rhs.x;
			y *= rhs.y;
		}

		void operator /=(const Vector3Int& rhs)
		{
			x /= rhs.x;
			y /= rhs.y;
		}

		Vector3Int operator +(const Vector3Int& rhs) const
		{
			return Vector3Int(x + rhs.x, y + rhs.y, z + rhs.z);
		}

		Vector3Int operator -(const Vector3Int& rhs) const
		{
			return Vector3Int(x - rhs.x, y - rhs.y, z - rhs.z);
		}

		Vector3Int operator *(const Vector3Int& rhs) const
		{
			return Vector3Int(x * rhs.x, y * rhs.y, z * rhs.z);
		}

		Vector3Int operator /(const Vector3Int& rhs) const
		{
			return Vector3Int(x / rhs.x, y / rhs.y, z / rhs.z);
		}

		bool operator ==(const Vector3Int& rhs) const
		{
			return x == rhs.x && y == rhs.y && z == rhs.z;
		}

		bool operator !=(const Vector3Int& rhs) const
		{
			return x != rhs.x || y != rhs.y || z != rhs.z;
		}

		bool operator >=(const Vector3Int& rhs) const
		{
			return Length() >= rhs.Length();
		}

		bool operator <=(const Vector3Int& rhs) const
		{
			return Length() <= rhs.Length();
		}

		bool operator >(const Vector3Int& rhs) const
		{
			return Length() > rhs.Length();
		}

		bool operator <(const Vector3Int& rhs) const
		{
			return Length() < rhs.Length();
		}

		// Int Operators

		void operator += (const int& rhs)
		{
			x += rhs;
			y += rhs;
			z += rhs;
		}

		void operator -=(const int& rhs)
		{
			x -= rhs;
			y -= rhs;
			z -= rhs;
		}

		void operator *=(const int& rhs)
		{
			x *= rhs;
			y *= rhs;
			z *= rhs;
		}

		void operator /=(const int& rhs)
		{
			x /= rhs;
			y /= rhs;
			z /= rhs;
		}

		Vector3Int operator +(const int& rhs) const
		{
			return Vector3Int(x + rhs, y + rhs, z + rhs);
		}

		Vector3Int operator -(const int& rhs) const
		{
			return Vector3Int(x - rhs, y - rhs, z - rhs);
		}

		Vector3Int operator *(const int& rhs) const
		{
			return Vector3Int(x * rhs, y * rhs, z * rhs);
		}

		Vector3Int operator /(const int& rhs) const
		{
			return Vector3Int(x / rhs, y / rhs, z / rhs);
		}

		bool operator ==(const int& rhs) const
		{
			return Length() == rhs;
		}

		bool operator !=(const int& rhs) const
		{
			return Length() != rhs;
		}

		bool operator >=(const int& rhs) const
		{
			return Length() >= rhs;
		}

		bool operator <=(const int& rhs) const
		{
			return Length() <= rhs;
		}

		bool operator >(const int& rhs) const
		{
			return Length() > rhs;
		}

		bool operator <(const int& rhs) const
		{
			return Length() < rhs;
		}

		// Conversions

		operator Vector2() const;
		operator Vector3() const;
		operator Vector4() const;

		operator Vector2Int() const;
		operator Vector4Int() const;
	};

	struct Vector4Int
	{
		int x = 0;
		int y = 0;
		int z = 0;
		int w = 0;

		Vector4Int()
		{
			x = 0;
			y = 0;
			z = 0;
			w = 0;
		}

		Vector4Int(int x, int y, int z, int w)
		{
			this->x = x;
			this->y = y;
			this->z = z;
			this->w = w;
		}

		// Functions

		Vector4Int Normalize() const
		{
			return *this / Length();
		}

		int Length() const
		{
			return sqrt(Dot(*this, *this));
		}

		static int Dot(const Vector4Int& lhs, const Vector4Int& rhs)
		{
			return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z + lhs.w * rhs.w;
		}

		// Vector4Int Operators

		Vector4Int operator -() const
		{
			return *this * -1;
		}

		void operator += (const Vector4Int& rhs)
		{
			x += rhs.x;
			y += rhs.y;
			z += rhs.z;
			w += rhs.w;
		}

		void operator -=(const Vector4Int& rhs)
		{
			x -= rhs.x;
			y -= rhs.x;
			z -= rhs.z;
			w -= rhs.w;
		}

		void operator *=(const Vector4Int& rhs)
		{
			x *= rhs.x;
			y *= rhs.y;
			z *= rhs.z;
			w *= rhs.w;
		}

		void operator /=(const Vector4Int& rhs)
		{
			x /= rhs.x;
			y /= rhs.y;
			z /= rhs.z;
			z /= rhs.w;
		}

		Vector4Int operator +(const Vector4Int& rhs) const
		{
			return Vector4Int(x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.w);
		}

		Vector4Int operator -(const Vector4Int& rhs) const
		{
			return Vector4Int(x - rhs.x, y - rhs.y, z - rhs.z, w - rhs.w);
		}

		Vector4Int operator *(const Vector4Int& rhs) const
		{
			return Vector4Int(x * rhs.x, y * rhs.y, z * rhs.z, w * rhs.w);
		}

		Vector4Int operator /(const Vector4Int& rhs) const
		{
			return Vector4Int(x / rhs.x, y / rhs.y, z / rhs.z, w / rhs.w);
		}

		bool operator ==(const Vector4Int& rhs) const
		{
			return x == rhs.x && y == rhs.y && z == rhs.z && w == rhs.w;
		}

		bool operator !=(const Vector4Int& rhs) const
		{
			return x != rhs.x || y != rhs.y || z != rhs.z || w != rhs.w;
		}

		bool operator >=(const Vector4Int& rhs) const
		{
			return Length() >= rhs.Length();
		}

		bool operator <=(const Vector4Int& rhs) const
		{
			return Length() <= rhs.Length();
		}

		bool operator >(const Vector4Int& rhs) const
		{
			return Length() > rhs.Length();
		}

		bool operator <(const Vector4Int& rhs) const
		{
			return Length() < rhs.Length();
		}

		// int Operators

		void operator += (const int& rhs)
		{
			x += rhs;
			y += rhs;
			z += rhs;
			w += rhs;
		}

		void operator -=(const int& rhs)
		{
			x -= rhs;
			y -= rhs;
			z -= rhs;
			w -= rhs;
		}

		void operator *=(const int& rhs)
		{
			x *= rhs;
			y *= rhs;
			z *= rhs;
			w *= rhs;
		}

		void operator /=(const int& rhs)
		{
			x /= rhs;
			y /= rhs;
			z /= rhs;
			w /= rhs;
		}

		Vector4Int operator +(const int& rhs) const
		{
			return Vector4Int(x + rhs, y + rhs, z + rhs, w + rhs);
		}

		Vector4Int operator -(const int& rhs) const
		{
			return Vector4Int(x - rhs, y - rhs, z - rhs, w - rhs);
		}

		Vector4Int operator *(const int& rhs) const
		{
			return Vector4Int(x * rhs, y * rhs, z * rhs, w * rhs);
		}

		Vector4Int operator /(const int& rhs) const
		{
			return Vector4Int(x / rhs, y / rhs, z / rhs, w / rhs);
		}

		bool operator ==(const int& rhs) const
		{
			return Length() == rhs;
		}

		bool operator !=(const int& rhs) const
		{
			return Length() != rhs;
		}

		bool operator >=(const int& rhs) const
		{
			return Length() >= rhs;
		}

		bool operator <=(const int& rhs) const
		{
			return Length() <= rhs;
		}

		bool operator >(const int& rhs) const
		{
			return Length() > rhs;
		}

		bool operator <(const int& rhs) const
		{
			return Length() < rhs;
		}

		// Conversions

		operator Vector2() const;
		operator Vector3() const;
		operator Vector4() const;

		operator Vector2Int() const;
		operator Vector3Int() const;
	};

	inline std::ostream& operator <<(std::ostream& os, const Vector2Int& rhs)
	{
		os << "(" << rhs.x << ", " << rhs.y << ")";
		return os;
	}

	inline std::ostream& operator <<(std::ostream& os, const Vector3Int& rhs)
	{
		os << "(" << rhs.x << ", " << rhs.y << ", " << rhs.z << ")";
		return os;
	}

	inline std::ostream& operator <<(std::ostream& os, const Vector4Int& rhs)
	{
		os << "(" << rhs.x << ", " << rhs.y << ", " << rhs.z << ", " << rhs.w << ")";
		return os;
	}
}