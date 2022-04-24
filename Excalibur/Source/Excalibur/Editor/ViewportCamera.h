#pragma once
#include <Merlin.h>

namespace Merlin::Editor
{
	class ViewportCamera : public Renderer::CameraRenderer
	{
	public:
		void MoveCamera();
		void Resize(float width, float height);

		Vector3 Position = Vector3(0, 0, 8);
		float CameraSpeed = 2.0f;
	};
}