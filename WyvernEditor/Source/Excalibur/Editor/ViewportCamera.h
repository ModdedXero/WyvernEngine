#pragma once
#include <Wyvern.h>

namespace Wyvern::Editor
{
	class ViewportCamera : public Renderer::CameraRenderer
	{
	public:
		ViewportCamera();

		void MoveCamera();
		void Resize(float width, float height);

		Transform* transform;
		float cameraSpeed = 2.0f;
	};
}