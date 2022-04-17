#include "ViewportCamera.h"

namespace Merlin::Editor
{
	void ViewportCamera::OnAttach()
	{
		m_Camera = AddComponent<Camera>();
		GetTransform()->position.z = -8;
		m_EditorOnly = true;
	}

	void ViewportCamera::MoveCamera()
	{
		if (Input::IsMouseButton(MouseCode::MOUSE_BUTTON_RIGHT))
		{
			if (Input::IsKey(KeyCode::W))
			{
				GetTransform()->position.y -= CameraSpeed * Timestep::GetDeltaTime();
			}

			if (Input::IsKey(KeyCode::S))
			{
				GetTransform()->position.y += CameraSpeed * Timestep::GetDeltaTime();
			}

			if (Input::IsKey(KeyCode::A))
			{
				GetTransform()->position.x -= CameraSpeed * Timestep::GetDeltaTime();
			}

			if (Input::IsKey(KeyCode::D))
			{
				GetTransform()->position.x += CameraSpeed * Timestep::GetDeltaTime();
			}
		}
	}

	void ViewportCamera::Resize(float width, float height)
	{
		m_Camera->ResizeView(width, height);
	}
}