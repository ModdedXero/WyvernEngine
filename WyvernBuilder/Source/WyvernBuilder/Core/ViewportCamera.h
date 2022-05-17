#pragma once
#include <Wyvern.h>

namespace Wyvern
{
	class ViewportCamera : public Renderer::CameraRenderer
	{
	public:
		ViewportCamera();

		void MoveCamera();

		Transform* transform;
		float cameraSpeed = 2.0f;
	};
}