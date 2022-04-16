#pragma once
#include <Merlin.h>

namespace Merlin
{
	class ViewportCamera : public Entity
	{
	public:
		virtual void OnAttach() override;
		virtual void OnUpdate() override;

		float CameraSpeed = 2.0f;
	private:
		Camera* m_Camera;
	};
}