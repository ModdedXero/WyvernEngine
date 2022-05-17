#include "ViewportCamera.h"

namespace Wyvern
{
	ViewportCamera::ViewportCamera()
	{
		transform = new Transform();
		transform->position.z = 0.5f;
	}

	void ViewportCamera::MoveCamera()
	{
		if (Input::IsMouseButton(MouseCode::MOUSE_BUTTON_RIGHT))
		{
			if (Input::IsKey(KeyCode::W))
			{
				transform->position.y -= cameraSpeed * Timestep::GetDeltaTime();
			}

			if (Input::IsKey(KeyCode::S))
			{
				transform->position.y += cameraSpeed * Timestep::GetDeltaTime();
			}

			if (Input::IsKey(KeyCode::A))
			{
				transform->position.x -= cameraSpeed * Timestep::GetDeltaTime();
			}

			if (Input::IsKey(KeyCode::D))
			{
				transform->position.x += cameraSpeed * Timestep::GetDeltaTime();
			}
		}
	}
}