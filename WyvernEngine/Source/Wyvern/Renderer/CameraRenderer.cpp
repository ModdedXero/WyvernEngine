#include "wvpch.h"
#include "CameraRenderer.h"

#include <Wyvern/Core/Components/Transform.h>
#include <Wyvern/Core/Application/Application.h>
#include <Wyvern/Core/AssetManager.h>

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>

namespace Wyvern::Render
{
	CameraRenderer::CameraRenderer()
		: m_Projection(1.0f), m_View(1.0f), m_OrthoSize(5.0f), m_FieldOfView(60.0f), m_ClipNear(0.3f), m_ClipFar(100.0f), m_AspectRatio(1.0f)
	{
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
		float lWidth = width < 1 ? 1 : width;
		float lHeight = height < 1 ? 1 : height;

		m_AspectRatio = lWidth / lHeight;
		m_CameraSize = { lWidth, lHeight };

		RecalculateProjection();
	}

	void CameraRenderer::SetShaderMatrices(Ref<Shader> shader, Transform* position)
	{
		RecalculateProjection();

		Vector3 pos = position->position;
		pos.y = -pos.y;

		m_View = Matrix4x4::Inverse(Transform::GetTransform(pos, position->rotation, position->scale)).GetNativeMatrix();

		shader->SetMatrix4("projection", m_Projection);
		shader->SetMatrix4("viewModel", m_View);
	}

	Vector2 CameraRenderer::WorldToScreenPoint(Vector3& pos)
	{
		//Display::Window& window = Application::Get().GetWindow();

		//auto point = s_Active->m_Projection * s_Active->m_View * glm::mat4(1.0f) * glm::vec4(pos.x, pos.y, 1.0f, 1.0f);

		//float xPos = ((point.x + 8) / 16) * window.GetWidth();
		//float yPos = window.GetHeight() - (((point.y + 8) / 16) * window.GetHeight());

		// Move to camera component and update window size method

		return Vector2();
	}

	void CameraRenderer::RecalculateProjection()
	{
		if (m_CameraMode == CameraMode::Perspective)
			m_Projection = glm::perspective(glm::radians(m_FieldOfView), m_AspectRatio, m_ClipNear, m_ClipFar);
		else
			m_Projection = glm::ortho(-m_OrthoSize * m_AspectRatio, m_OrthoSize * m_AspectRatio, -m_OrthoSize, m_OrthoSize, m_ClipNear, m_ClipFar);
	}
}