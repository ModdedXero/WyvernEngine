#pragma once

#include <Wyvern.h>

namespace Wyvern
{
	class ViewportCamera : public Render::CameraRenderer
	{
	public:
		ViewportCamera();

		void MoveCamera();
		void OnScroll(Events::MouseScrolledEvent& e);

		Transform* transform;
		float cameraSpeed = 2.0f;

	private:
		Vector2 m_InitialMousePosition;
	};
}