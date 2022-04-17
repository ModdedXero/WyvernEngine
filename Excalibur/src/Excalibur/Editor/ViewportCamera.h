#pragma once
#include <Merlin.h>

namespace Merlin::Editor
{
	class ViewportCamera : public Entity
	{
	public:
		virtual void OnAttach() override;

		void MoveCamera();
		void Resize(float width, float height);

		float CameraSpeed = 2.0f;
	private:
		Camera* m_Camera;
	};
}