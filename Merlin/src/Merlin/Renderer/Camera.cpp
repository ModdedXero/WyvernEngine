#include "mlpch.h"
#include "Camera.h"

#include <Merlin/Core/Application.h>
#include <Merlin/Renderer/ResourceManager.h>

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>

namespace Merlin
{
	Camera* Camera::s_Main = nullptr;

	Camera::Camera()
		: m_Projection(1.0f), m_View(1.0f)
	{
		s_Main = this;

		m_Projection = glm::perspective(glm::radians(60.0f),
			(float)Application::Get().GetWindow().GetWidth() / (float)Application::Get().GetWindow().GetHeight(), 0.1f, 100.0f);

		transform = Vector3(0, 0, 0);
	}

	Camera::Camera(Vector3 position)
		: m_Projection(1.0f), m_View(1.0f)
	{
		s_Main = this;

		m_Projection = glm::perspective(glm::radians(60.0f),
			(float)Application::Get().GetWindow().GetWidth() / (float)Application::Get().GetWindow().GetHeight(), 0.1f, 100.0f);

		transform = position;
	}

	void Camera::RecalculateMatrix()
	{
		m_View = transform.localToWorldMatrix();
	}

	void Camera::SetShaderMatrix()
	{
		ResourceManager::GetShader("FlatShader").SetMatrix4("view", GetViewMatrix());
		ResourceManager::GetShader("FlatShader").SetMatrix4("projection", GetProjectionMatrix());
	}
}