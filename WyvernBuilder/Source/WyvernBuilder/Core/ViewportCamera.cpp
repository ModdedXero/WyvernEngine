#include "ViewportCamera.h"

#include <glm/glm.hpp>

namespace Wyvern
{
	ViewportCamera::ViewportCamera()
	{
		transform = new Transform();
		SetCameraMode(Render::CameraMode::Perspective);
		transform->position.z = 10.0f;
	}

	void ViewportCamera::MoveCamera()
	{
		if (Input::IsMouseButton(MouseCode::MOUSE_BUTTON_RIGHT))
		{
			ImGui::GetIO().MousePos = { m_InitialMousePosition.x, m_InitialMousePosition.y };

			glfwSetInputMode(Application::Get().GetWindow().GetNativeWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

			const Vector2& mouse = Input::MousePosition();
			Vector2 delta = (mouse - m_InitialMousePosition) * 0.3f;
			m_InitialMousePosition = mouse;

			transform->rotation.x -= delta.y;
			transform->rotation.y -= delta.x;

			if (Input::IsKey(KeyCode::W))
			{
				transform->position += transform->Forward() * 0.5f;
			}

			if (Input::IsKey(KeyCode::S))
			{
				transform->position += transform->Back() * 0.5f;
			}

			if (Input::IsKey(KeyCode::A))
			{
				transform->position += transform->Left() * 0.5f;
			}

			if (Input::IsKey(KeyCode::D))
			{
				transform->position += transform->Right() * 0.5f;
			}
		}
		else
		{
			glfwSetInputMode(Application::Get().GetWindow().GetNativeWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		}

		m_InitialMousePosition = Input::MousePosition();
	}

	void ViewportCamera::OnScroll(Events::MouseScrolledEvent& e)
	{
		if (Input::IsMouseButton(MouseCode::MOUSE_BUTTON_RIGHT))
			transform->position.z -= e.GetDirection();
	}
}