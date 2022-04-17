#pragma once

#include <glm/glm.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>

#include <iostream>

namespace Merlin
{
	struct Vector2
	{
		Vector2(float x, float y)
		{
			this->x = x;
			this->y = y;
		}

		Vector2()
		{
			this->x = 0.0f;
			this->y = 0.0f;
		}

		float x = 0.0f;
		float y = 0.0f;

		// Local Functions

		Vector2 Normalize()
		{
			return *this / Length();
		}

		float Length()
		{
			return sqrt(Dot(*this, *this));
		}

		// Static Functions

		static float Dot(const Vector2& vec1, const Vector2& vec2)
		{
			return vec1.x * vec2.x + vec1.y * vec2.y;
		}

		// Vector2 Operators

		Vector2& operator +=(const Vector2& other)
		{
			x = x + other.x;
			y = y + other.y;
			return *this;
		}

		Vector2& operator -=(const Vector2& other)
		{
			x = x - other.x;
			y = y - other.y;
			return *this;
		}

		Vector2& operator *=(const Vector2& other)
		{
			x = x * other.x;
			y = y * other.y;
			return *this;
		}


		Vector2 operator -() const
		{
			return *this * -1;
		}

		Vector2 operator +(const Vector2& other) const
		{
			return Vector2(x + other.x, y + other.y);
		}

		Vector2 operator -(const Vector2& other) const
		{
			return Vector2(x - other.x, y - other.y);
		}

		Vector2 operator *(const Vector2& other) const
		{
			return Vector2(x * other.x, y * other.y);
		}

		bool operator ==(const Vector2& other) const
		{
			return (x == other.x) && (y == other.y);
		}

		bool operator !=(const Vector2& other) const
		{
			return (x != other.x) || (y != other.y);
		}

		bool operator >(const Vector2& other) const
		{
			return sqrt(Dot(*this, *this)) < sqrt(Dot(other, other));
		}

		bool operator <(const Vector2& other) const
		{
			return sqrt(Dot(*this, *this)) < sqrt(Dot(other, other));
		}

		// Float Operators

		Vector2 operator +(const float& other) const
		{
			return Vector2(x + other, y + other);
		}

		Vector2 operator *(const float& other) const
		{
			return Vector2(x * other, y * other);
		}

		Vector2 operator /(const float& other) const
		{
			return Vector2(x / other, y / other);
		}
	};

	struct Vector3
	{
		Vector3(float x, float y, float z)
		{
			this->x = x;
			this->y = y;
			this->z = z;
		}

		Vector3()
		{
			this->x = 0.0f;
			this->y = 0.0f;
			this->y = 0.0f;
		}

		float x = 0.0f;
		float y = 0.0f;
		float z = 0.0f;

		glm::vec3 glmPosition() { return glm::vec3(x, y, z); }

		Vector3& operator +=(const Vector3& other)
		{
			x = x + other.x;
			y = y + other.y;
			z = z + other.z;
			return *this;
		}

		Vector3& operator -=(const Vector3& other)
		{
			x = x - other.x;
			y = y - other.y;
			z = z - other.z;
			return *this;
		}

		Vector3 operator -() const
		{
			return *this * -1;
		}

		Vector3 operator +(const Vector3& other) const
		{
			return Vector3(x + other.x, y + other.y, z + other.z);
		}

		Vector3 operator -(const Vector3& other) const
		{
			return Vector3(x - other.x, y - other.y, z - other.z);
		}

		Vector3 operator *(const Vector3& other) const
		{
			return Vector3(x * other.x, y * other.y, z * other.z);
		}

		Vector3 operator *(const float& other) const
		{
			return Vector3(x * other, y * other, z * other);
		}

		Vector3 operator /(const float& other) const
		{
			return Vector3(x / other, y / other, z / other);
		}

		operator Vector2() const
		{
			return Vector2(x, y);
		}

		Vector3& operator +=(const Vector2& other)
		{
			x = x + other.x;
			y = y + other.y;
			return *this;
		}

		Vector3& operator -=(const Vector2& other)
		{
			x = x - other.x;
			y = y - other.y;
			return *this;
		}

		Vector3 operator +(const Vector2& other) const
		{
			return Vector3(x + other.x, y + other.y, z);
		}

		Vector3 operator -(const Vector2& other) const
		{
			return Vector3(x - other.x, y - other.y, z);
		}

		Vector3 operator *(const Vector2& other) const
		{
			return Vector3(x * other.x, y * other.y, z);
		}
	};

	struct Vector4
	{
		Vector4(float x, float y, float z, float w)
		{
			this->x = x;
			this->y = y;
			this->z = z;
			this->w = w;
		}

		Vector4()
		{
			this->x = 0.0f;
			this->y = 0.0f;
			this->z = 0.0f;
			this->w = 0.0f;
		}

		float x = 0.0f;
		float y = 0.0f;
		float z = 0.0f;
		float w = 0.0f;

		// Vector4 Operators

		Vector4 operator *(const Vector4& other) const
		{
			return Vector4(x * other.x, y * other.y, z * other.z, w * other.w);
		}
	};

	inline std::ostream& operator <<(std::ostream& os, const Vector2& vec)
	{
		os << "(" << vec.x << ", " << vec.y << ")";
		return os;
	}

	inline std::ostream& operator <<(std::ostream& os, const Vector3& vec)
	{
		os << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
		return os;
	}
}