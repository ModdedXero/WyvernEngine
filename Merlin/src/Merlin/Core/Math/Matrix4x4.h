#pragma once

#include "Vector.h"

#include <glm/glm.hpp>

namespace Merlin
{
	struct Matrix4x4
	{
		Matrix4x4(float identity)
		{
			m_Matrix = glm::mat4(identity);
		}

		Matrix4x4(glm::mat4 matrix)
		{
			m_Matrix = matrix;
		}

		// Helpers

		static Matrix4x4 Translate(const Vector3& vector)
		{
			return glm::translate(glm::mat4(1.0f), glm::vec3(vector.x, vector.y, vector.z));
		}

		static Matrix4x4 Rotate(const Vector3& rotation)
		{
			return glm::rotate(glm::mat4(1.0f), glm::radians(rotation.x), { 1.0f, 0.0f, 0.0f })
				* glm::rotate(glm::mat4(1.0f), glm::radians(rotation.y), { 0.0f, 1.0f, 0.0f })
				* glm::rotate(glm::mat4(1.0f), glm::radians(rotation.z), { 0.0f, 0.0f, 1.0f });
		}

		// Matrix Operators

		void operator =(const glm::mat4& mat)
		{
			this->m_Matrix = mat;
		}

		Matrix4x4 operator *(const glm::mat4& mat)
		{
			return this->m_Matrix * mat;
		}

		Matrix4x4 operator *(const Matrix4x4& other)
		{
			return this->m_Matrix * other.m_Matrix;
		}

		// Vec4 Operators

		glm::vec<4, float, glm::packed_highp> operator *(const glm::vec4 vec)
		{
			return this->m_Matrix * vec;
		}

		// Vec3 Operators

	private:
		glm::mat4 m_Matrix;
	};
}