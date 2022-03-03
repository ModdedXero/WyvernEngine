#pragma once

#include <glm/glm.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>

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

		operator Vector2() const
		{
			Vector2 vec2 = Vector2(x, y);
			return vec2;
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
	};
}