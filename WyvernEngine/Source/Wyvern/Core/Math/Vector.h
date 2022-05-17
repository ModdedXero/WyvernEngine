#pragma once

#include <glm/glm.hpp>

#include <iostream>

namespace Wyvern
{
	struct Vector2Int;
	struct Vector3Int;
	struct Vector4Int;

	struct Vector3;
	struct Vector4;

	struct Vector2
	{
		float x = 0;
		float y = 0;

		Vector2()
		{
			x = 0;
			y = 0;
		}

		Vector2(float x, float y)
		{
			this->x = x;
			this->y = y;
		}

		// Functions

		Vector2 Normalize() const
		{
			return *this / Length();
		}

		float Length() const
		{
			return sqrt(Dot(*this, *this));
		}

		static float Dot(const Vector2& lhs, const Vector2& rhs)
		{
			return lhs.x * rhs.x + lhs.y * rhs.y;
		}

		// Vector2 Operators

		Vector2 operator -() const
		{
			return *this * -1;
		}

		void operator += (const Vector2& rhs)
		{
			x += rhs.x;
			y += rhs.y;
		}

		void operator -=(const Vector2& rhs)
		{
			x -= rhs.x;
			y -= rhs.x;
		}

		void operator *=(const Vector2& rhs)
		{
			x *= rhs.x;
			y *= rhs.y;
		}

		void operator /=(const Vector2& rhs)
		{
			x /= rhs.x;
			y /= rhs.y;
		}

		Vector2 operator +(const Vector2& rhs) const
		{
			return Vector2(x + rhs.x, y + rhs.y);
		}

		Vector2 operator -(const Vector2& rhs) const
		{
			return Vector2(x - rhs.x, y - rhs.y);
		}

		Vector2 operator *(const Vector2& rhs) const
		{
			return Vector2(x * rhs.x, y * rhs.y);
		}

		Vector2 operator /(const Vector2& rhs) const
		{
			return Vector2(x / rhs.x, y / rhs.y);
		}

		bool operator ==(const Vector2& rhs) const
		{
			return x == rhs.x && y == rhs.y;
		}

		bool operator !=(const Vector2& rhs) const
		{
			return x != rhs.x || y != rhs.y;
		}

		bool operator >=(const Vector2& rhs) const
		{
			return Length() >= rhs.Length();
		}

		bool operator <=(const Vector2& rhs) const
		{
			return Length() <= rhs.Length();
		}

		bool operator >(const Vector2& rhs) const
		{
			return Length() > rhs.Length();
		}

		bool operator <(const Vector2& rhs) const
		{
			return Length() < rhs.Length();
		}

		// Float Operators

		void operator += (const float& rhs)
		{
			x += rhs;
			y += rhs;
		}

		void operator -=(const float& rhs)
		{
			x -= rhs;
			y -= rhs;
		}

		void operator *=(const float& rhs)
		{
			x *= rhs;
			y *= rhs;
		}

		void operator /=(const float& rhs)
		{
			x /= rhs;
			y /= rhs;
		}

		Vector2 operator +(const float& rhs) const
		{
			return Vector2(x + rhs, y + rhs);
		}

		Vector2 operator -(const float& rhs) const
		{
			return Vector2(x - rhs, y - rhs);
		}

		Vector2 operator *(const float& rhs) const
		{
			return Vector2(x * rhs, y * rhs);
		}

		Vector2 operator /(const float& rhs) const
		{
			return Vector2(x / rhs, y / rhs);
		}

		bool operator ==(const float& rhs) const
		{
			return Length() == rhs;
		}

		bool operator !=(const float& rhs) const
		{
			return Length() != rhs;
		}

		bool operator >=(const float& rhs) const
		{
			return Length() >= rhs;
		}

		bool operator <=(const float& rhs) const
		{
			return Length() <= rhs;
		}

		bool operator >(const float& rhs) const
		{
			return Length() > rhs;
		}

		bool operator <(const float& rhs) const
		{
			return Length() < rhs;
		}

		// Conversions

		operator Vector3() const;
		operator Vector4() const;

		operator Vector2Int() const;
		operator Vector3Int() const;
		operator Vector4Int() const;
	};

	struct Vector3
	{
		float x = 0;
		float y = 0;
		float z = 0;

		Vector3()
		{
			x = 0;
			y = 0;
			z = 0;
		}

		Vector3(float x, float y, float z)
		{
			this->x = x;
			this->y = y;
			this->z = z;
		}

		// Functions

		Vector3 Normalize() const
		{
			return *this / Length();
		}

		float Length() const
		{
			return sqrt(Dot(*this, *this));
		}

		static float Dot(const Vector3& lhs, const Vector3& rhs)
		{
			return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
		}

		// Vector3 Operators

		Vector3 operator -() const
		{
			return *this * -1;
		}

		void operator += (const Vector3& rhs)
		{
			x += rhs.x;
			y += rhs.y;
			z += rhs.z;
		}

		void operator -=(const Vector3& rhs)
		{
			x -= rhs.x;
			y -= rhs.x;
			z -= rhs.z;
		}

		void operator *=(const Vector3& rhs)
		{
			x *= rhs.x;
			y *= rhs.y;
			z *= rhs.z;
		}

		void operator /=(const Vector3& rhs)
		{
			x /= rhs.x;
			y /= rhs.y;
			z /= rhs.z;
		}

		Vector3 operator +(const Vector3& rhs) const
		{
			return Vector3(x + rhs.x, y + rhs.y, z + rhs.z);
		}

		Vector3 operator -(const Vector3& rhs) const
		{
			return Vector3(x - rhs.x, y - rhs.y, z - rhs.z);
		}

		Vector3 operator *(const Vector3& rhs) const
		{
			return Vector3(x * rhs.x, y * rhs.y, z * rhs.z);
		}

		Vector3 operator /(const Vector3& rhs) const
		{
			return Vector3(x / rhs.x, y / rhs.y, z / rhs.z);
		}

		bool operator ==(const Vector3& rhs) const
		{
			return x == rhs.x && y == rhs.y && z == rhs.z;
		}

		bool operator !=(const Vector3& rhs) const
		{
			return x != rhs.x || y != rhs.y || z != rhs.z;
		}

		bool operator >=(const Vector3& rhs) const
		{
			return Length() >= rhs.Length();
		}

		bool operator <=(const Vector3& rhs) const
		{
			return Length() <= rhs.Length();
		}

		bool operator >(const Vector3& rhs) const
		{
			return Length() > rhs.Length();
		}

		bool operator <(const Vector3& rhs) const
		{
			return Length() < rhs.Length();
		}

		// Float Operators

		void operator += (const float& rhs)
		{
			x += rhs;
			y += rhs;
			z += rhs;
		}

		void operator -=(const float& rhs)
		{
			x -= rhs;
			y -= rhs;
			z -= rhs;
		}

		void operator *=(const float& rhs)
		{
			x *= rhs;
			y *= rhs;
			z *= rhs;
		}

		void operator /=(const float& rhs)
		{
			x /= rhs;
			y /= rhs;
			z /= rhs;
		}

		Vector3 operator +(const float& rhs) const
		{
			return Vector3(x + rhs, y + rhs, z + rhs);
		}

		Vector3 operator -(const float& rhs) const
		{
			return Vector3(x - rhs, y - rhs, z - rhs);
		}

		Vector3 operator *(const float& rhs) const
		{
			return Vector3(x * rhs, y * rhs, z * rhs);
		}

		Vector3 operator /(const float& rhs) const
		{
			return Vector3(x / rhs, y / rhs, z / rhs);
		}

		bool operator ==(const float& rhs) const
		{
			return Length() == rhs;
		}

		bool operator !=(const float& rhs) const
		{
			return Length() != rhs;
		}

		bool operator >=(const float& rhs) const
		{
			return Length() >= rhs;
		}

		bool operator <=(const float& rhs) const
		{
			return Length() <= rhs;
		}

		bool operator >(const float& rhs) const
		{
			return Length() > rhs;
		}

		bool operator <(const float& rhs) const
		{
			return Length() < rhs;
		}

		// Temporary Conversions

		Vector3(glm::vec<4, float, glm::packed_highp> vec)
		{
			this->x = vec.x;
			this->y = vec.y;
			this->z = vec.z;
		}

		operator glm::vec3() const;

		void operator =(const glm::vec3& other)
		{
			x = other.x;
			y = other.y;
			z = other.z;
		}

		Vector3& operator +=(const glm::vec3& other)
		{
			x = x + other.x;
			y = y + other.y;
			z = z + other.z;
			return *this;
		}

		// Conversions

		operator Vector2() const;
		operator Vector4() const;

		operator Vector2Int() const;
		operator Vector3Int() const;
		operator Vector4Int() const;
	};

	struct Vector4
	{
		float x = 0;
		float y = 0;
		float z = 0;
		float w = 0;

		Vector4()
		{
			x = 0;
			y = 0;
			z = 0;
			w = 0;
		}

		Vector4(float x, float y, float z, float w)
		{
			this->x = x;
			this->y = y;
			this->z = z;
			this->w = w;
		}

		// Functions

		Vector4 Normalize() const
		{
			return *this / Length();
		}

		float Length() const
		{
			return sqrt(Dot(*this, *this));
		}

		static float Dot(const Vector4& lhs, const Vector4& rhs)
		{
			return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z + lhs.w * rhs.w;
		}

		// Vector4 Operators

		Vector4 operator -() const
		{
			return *this * -1;
		}

		void operator += (const Vector4& rhs)
		{
			x += rhs.x;
			y += rhs.y;
			z += rhs.z;
			w += rhs.w;
		}

		void operator -=(const Vector4& rhs)
		{
			x -= rhs.x;
			y -= rhs.x;
			z -= rhs.z;
			w -= rhs.w;
		}

		void operator *=(const Vector4& rhs)
		{
			x *= rhs.x;
			y *= rhs.y;
			z *= rhs.z;
			w *= rhs.w;
		}

		void operator /=(const Vector4& rhs)
		{
			x /= rhs.x;
			y /= rhs.y;
			z /= rhs.z;
			z /= rhs.w;
		}

		Vector4 operator +(const Vector4& rhs) const
		{
			return Vector4(x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.w);
		}

		Vector4 operator -(const Vector4& rhs) const
		{
			return Vector4(x - rhs.x, y - rhs.y, z - rhs.z, w - rhs.w);
		}

		Vector4 operator *(const Vector4& rhs) const
		{
			return Vector4(x * rhs.x, y * rhs.y, z * rhs.z, w * rhs.w);
		}

		Vector4 operator /(const Vector4& rhs) const
		{
			return Vector4(x / rhs.x, y / rhs.y, z / rhs.z, w / rhs.w);
		}

		bool operator ==(const Vector4& rhs) const
		{
			return x == rhs.x && y == rhs.y && z == rhs.z && w == rhs.w;
		}

		bool operator !=(const Vector4& rhs) const
		{
			return x != rhs.x || y != rhs.y || z != rhs.z || w != rhs.w;
		}

		bool operator >=(const Vector4& rhs) const
		{
			return Length() >= rhs.Length();
		}

		bool operator <=(const Vector4& rhs) const
		{
			return Length() <= rhs.Length();
		}

		bool operator >(const Vector4& rhs) const
		{
			return Length() > rhs.Length();
		}

		bool operator <(const Vector4& rhs) const
		{
			return Length() < rhs.Length();
		}

		// Float Operators

		void operator += (const float& rhs)
		{
			x += rhs;
			y += rhs;
			z += rhs;
			w += rhs;
		}

		void operator -=(const float& rhs)
		{
			x -= rhs;
			y -= rhs;
			z -= rhs;
			w -= rhs;
		}

		void operator *=(const float& rhs)
		{
			x *= rhs;
			y *= rhs;
			z *= rhs;
			w *= rhs;
		}

		void operator /=(const float& rhs)
		{
			x /= rhs;
			y /= rhs;
			z /= rhs;
			w /= rhs;
		}

		Vector4 operator +(const float& rhs) const
		{
			return Vector4(x + rhs, y + rhs, z + rhs, w + rhs);
		}

		Vector4 operator -(const float& rhs) const
		{
			return Vector4(x - rhs, y - rhs, z - rhs, w - rhs);
		}

		Vector4 operator *(const float& rhs) const
		{
			return Vector4(x * rhs, y * rhs, z * rhs, w * rhs);
		}

		Vector4 operator /(const float& rhs) const
		{
			return Vector4(x / rhs, y / rhs, z / rhs, w / rhs);
		}

		bool operator ==(const float& rhs) const
		{
			return Length() == rhs;
		}

		bool operator !=(const float& rhs) const
		{
			return Length() != rhs;
		}

		bool operator >=(const float& rhs) const
		{
			return Length() >= rhs;
		}

		bool operator <=(const float& rhs) const
		{
			return Length() <= rhs;
		}

		bool operator >(const float& rhs) const
		{
			return Length() > rhs;
		}

		bool operator <(const float& rhs) const
		{
			return Length() < rhs;
		}

		// Conversions

		operator Vector2() const;
		operator Vector3() const;

		operator Vector2Int() const;
		operator Vector3Int() const;
		operator Vector4Int() const;
	};

	inline std::ostream& operator <<(std::ostream& os, const Vector2& rhs)
	{
		os << "(" << rhs.x << ", " << rhs.y << ")";
		return os;
	}

	inline std::ostream& operator <<(std::ostream& os, const Vector3& rhs)
	{
		os << "(" << rhs.x << ", " << rhs.y << ", " << rhs.z << ")";
		return os;
	}

	inline std::ostream& operator <<(std::ostream& os, const Vector4& rhs)
	{
		os << "(" << rhs.x << ", " << rhs.y << ", " << rhs.z << ", " << rhs.w << ")";
		return os;
	}
}