#pragma once

#include <Wyvern/Core/Scene/Component.h>
#include <Wyvern/Renderer/CameraRenderer.h>

namespace Wyvern
{
	struct Camera : public Component
	{
		Renderer::CameraRenderer* GetRenderer() { return m_Renderer; }

		bool IsActive() { return m_IsActiveCamera; }
		void SetActive() { SetActiveCamera(this); }

		static Camera* GetActiveCamera() { return s_ActiveCamera; }
		static void SetActiveCamera(Camera* camera) { camera->m_IsActiveCamera = true; s_ActiveCamera = camera; }

		WV_SERIALIZE_COMPONENT(Camera)
		WV_SERIALIZE_VARIABLE(bool, m_IsActiveCamera)
		WV_SERIALIZE_COMPONENT_END
	private:
		Renderer::CameraRenderer* m_Renderer = new Renderer::CameraRenderer();

		static Camera* s_ActiveCamera;

		bool m_IsActiveCamera;
	};
}