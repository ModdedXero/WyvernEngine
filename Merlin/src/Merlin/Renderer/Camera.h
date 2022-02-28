#pragma once

#include <Merlin/Core/Math/Vector.h>

#include <glm/glm.hpp>

namespace Merlin
{
	class Camera
	{
	public:
		Camera();
		Camera(Vector3 position);

		void RecalculateMatrix();
		void SetShaderMatrix();

		glm::mat4& GetViewMatrix() { return m_View; }
		glm::mat4& GetProjectionMatrix() { return m_Projection; }
		glm::mat4& GetViewProjectionMatrix() { return m_Projection * m_View; }

		Vector3 transform;

		static Camera& Main() { return *s_Main; }
	private:
		static Camera* s_Main;

		glm::mat4 m_View;
		glm::mat4 m_Projection;
	};
}