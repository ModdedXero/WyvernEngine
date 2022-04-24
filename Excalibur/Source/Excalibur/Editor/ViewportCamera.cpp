#include "ViewportCamera.h"

namespace Merlin::Editor
{
	void ViewportCamera::MoveCamera()
	{
		if (Input::IsMouseButton(MouseCode::MOUSE_BUTTON_RIGHT))
		{
			if (Input::IsKey(KeyCode::W))
			{
				Position.y -= CameraSpeed * Timestep::GetDeltaTime();
			}

			if (Input::IsKey(KeyCode::S))
			{
				Position.y += CameraSpeed * Timestep::GetDeltaTime();
			}

			if (Input::IsKey(KeyCode::A))
			{
				Position.x -= CameraSpeed * Timestep::GetDeltaTime();
			}

			if (Input::IsKey(KeyCode::D))
			{
				Position.x += CameraSpeed * Timestep::GetDeltaTime();
			}
		}
	}

	void ViewportCamera::Resize(float width, float height)
	{
		ResizeView(width, height);
	}
}