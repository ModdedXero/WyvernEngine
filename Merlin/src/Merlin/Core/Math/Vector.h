#pragma once

#include "Merlin/Core/Log.h"

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
		glm::mat4 localToWorldMatrix() { return glm::translate(glm::mat4(1.0f), glmPosition()); }

		Vector3& operator +=(const Vector3& other)
		{
			x = x + other.x;
			y = y + other.y;
			z = z + other.z;
			return *this;
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
	};

	inline std::ostream& operator <<(std::ostream& os, const Vector3& vec)
	{
		os << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
		return os;
	}

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
	};
}