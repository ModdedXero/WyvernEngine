#include "ViewportCamera.h"

namespace Merlin
{
	void ViewportCamera::OnAttach()
	{
		AddComponent<Camera>();
		GetTransform()->position.z = 8;
	}

	void ViewportCamera::OnUpdate()
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