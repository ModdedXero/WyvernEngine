#include "mlpch.h"
#include "CameraRenderer.h"

#include <Merlin/Core/Application.h>

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>

namespace Merlin::Renderer
{
	CameraRenderer* CameraRenderer::s_Active = nullptr;

	CameraRenderer::CameraRenderer()
		: m_Projection(1.0f), m_View(1.0f), m_OrthoSize(5.0f), m_FieldOfView(60.0f), m_ClipNear(0.3f), m_ClipFar(100.0f), m_AspectRatio(1.0f)
	{
		if (s_Active == nullptr) s_Active = this;

		float aspectRatio = (float)Application::Get().GetWindow().GetWidth() / (float)Application::Get().GetWindow().GetHeight();

		if (m_CameraMode == CameraMode::Perspective)
			m_Projection = glm::perspective(glm::radians(m_FieldOfView), aspectRatio, m_ClipNear, m_ClipFar);
		else
			m_Projection = glm::ortho(-m_OrthoSize * m_AspectRatio, m_OrthoSize * m_AspectRatio, -m_OrthoSize, m_OrthoSize, m_ClipNear, m_ClipFar);
	}

	void CameraRenderer::SetCameraMode(CameraMode mode)
	{
		m_CameraMode = mode;

		RecalculateProjection();
	}

	void CameraRenderer::SetProjection(float width, float height)
	{
		m_AspectRatio = width / height > 0 ? width / height : 0.0001f;

		RecalculateProjection();
	}

	void CameraRenderer::ResizeView(float width, float height)
	{
		float lWidth = width < 1 ? 1 : width;
		float lHeight = height < 1 ? 1 : height;

		SetProjection(lWidth, lHeight);
		glViewport(0, 0, lWidth, lHeight);
	}

	void CameraRenderer::SetShaderMatrices(Ref<Shader> shader, const Vector3& position)
	{
		RecalculateProjection();

		m_View = glm::translate(glm::mat4(1.0f), glm::vec3(-position.x, -position.y, -position.z));

		shader->SetMatrix4("projection", m_Projection);
		shader->SetMatrix4("viewModel", m_View * glm::mat4(1.0f));
	}

	Vector2 CameraRenderer::WorldToScreenPoint(Vector3& pos)
	{
		Display::Window& window = Application::Get().GetWindow();

		auto point = s_Active->m_Projection * s_Active->m_View * glm::mat4(1.0f) * glm::vec4(pos.x, pos.y, 1.0f, 1.0f);

		float xPos = ((point.x + 8) / 16) * window.GetWidth();
		float yPos = window.GetHeight() - (((point.y + 8) / 16) * window.GetHeight());

		return Vector2(xPos, yPos);
	}

	void CameraRenderer::RecalculateProjection()
	{
		if (m_CameraMode == CameraMode::Perspective)
			m_Projection = glm::perspective(glm::radians(m_FieldOfView), m_AspectRatio, m_ClipNear, m_ClipFar);
		else
			m_Projection = glm::ortho(-m_OrthoSize * m_AspectRatio, m_OrthoSize * m_AspectRatio, -m_OrthoSize, m_OrthoSize, m_ClipNear, m_ClipFar);
	}
}