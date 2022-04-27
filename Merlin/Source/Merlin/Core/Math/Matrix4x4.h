#pragma once

#include "Vector.h"

#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/matrix_decompose.hpp>

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

		glm::mat4 GetNativeMatrix() { return m_Matrix; }

		// Helpers

		static Matrix4x4 Translate(const Vector3& vector)
		{
			return glm::translate(glm::mat4(1.0f), glm::vec3(vector.x, vector.y, vector.z));
		}

		static Matrix4x4 Rotate(const Vector3& rotation)
		{
			return glm::toMat4(glm::quat(glm::vec3(rotation.x, rotation.y, rotation.z)));

			return glm::rotate(glm::mat4(1.0f), glm::radians(rotation.x), { 1.0f, 0.0f, 0.0f })
				* glm::rotate(glm::mat4(1.0f), glm::radians(rotation.y), { 0.0f, 1.0f, 0.0f })
				* glm::rotate(glm::mat4(1.0f), glm::radians(rotation.z), { 0.0f, 0.0f, 1.0f });
		}

		static Matrix4x4 Scale(const Vector3& scale)
		{
			return glm::scale(glm::mat4(1.0f), glm::vec3(scale.x, scale.y, scale.z));
		}

		static Matrix4x4 Inverse(const Matrix4x4& other)
		{
			return glm::inverse(other.m_Matrix);
		}

		static bool Decompose(const Matrix4x4& transform, glm::vec3& position, glm::vec3& rotation, glm::vec3& scale)
		{
			// From glm::decompose in matrix_decompose.inl

			using namespace glm;
			using T = float;

			mat4 LocalMatrix(transform.m_Matrix);

			// Normalize the matrix.
			if (epsilonEqual(LocalMatrix[3][3], static_cast<float>(0), epsilon<T>()))
				return false;

			// First, isolate perspective.  This is the messiest.
			if (
				epsilonNotEqual(LocalMatrix[0][3], static_cast<T>(0), epsilon<T>()) ||
				epsilonNotEqual(LocalMatrix[1][3], static_cast<T>(0), epsilon<T>()) ||
				epsilonNotEqual(LocalMatrix[2][3], static_cast<T>(0), epsilon<T>()))
			{
				// Clear the perspective partition
				LocalMatrix[0][3] = LocalMatrix[1][3] = LocalMatrix[2][3] = static_cast<T>(0);
				LocalMatrix[3][3] = static_cast<T>(1);
			}

			// Next take care of translation (easy).
			position = vec3(LocalMatrix[3]);
			LocalMatrix[3] = vec4(0, 0, 0, LocalMatrix[3].w);

			vec3 Row[3], Pdum3;

			// Now get scale and shear.
			for (length_t i = 0; i < 3; ++i)
				for (length_t j = 0; j < 3; ++j)
					Row[i][j] = LocalMatrix[i][j];

			// Compute X scale factor and normalize first row.
			scale.x = length(Row[0]);
			Row[0] = detail::scale(Row[0], static_cast<T>(1));
			scale.y = length(Row[1]);
			Row[1] = detail::scale(Row[1], static_cast<T>(1));
			scale.z = length(Row[2]);
			Row[2] = detail::scale(Row[2], static_cast<T>(1));

			// At this point, the matrix (in rows[]) is orthonormal.
			// Check for a coordinate system flip.  If the determinant
			// is -1, then negate the matrix and the scaling factors.
#if 0
			Pdum3 = cross(Row[1], Row[2]); // v3Cross(row[1], row[2], Pdum3);
			if (dot(Row[0], Pdum3) < 0)
			{
				for (length_t i = 0; i < 3; i++)
				{
					scale[i] *= static_cast<T>(-1);
					Row[i] *= static_cast<T>(-1);
				}
			}
#endif
			rotation.y = asin(-Row[0][2]);
			if (cos(rotation.y) != 0) {
				rotation.x = atan2(Row[1][2], Row[2][2]);
				rotation.z = atan2(Row[0][1], Row[0][0]);
			}
			else 
			{
				rotation.x = atan2(-Row[2][0], Row[1][1]);
				rotation.z = 0;
			}


			return true;
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

		Matrix4x4 operator +(const glm::mat4& mat)
		{
			return this->m_Matrix + mat;
		}

		Matrix4x4 operator +(const Matrix4x4& other)
		{
			return this->m_Matrix + other.m_Matrix;
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