#pragma once

#include <Wyvern/Core/Scene/Component.h>
#include <Wyvern/Renderer/CameraRenderer.h>

namespace Wyvern
{
	struct Camera : public Component
	{
		Camera()
		{
			if (!s_ActiveCamera) SetActiveCamera(this);
		}

		Renderer::CameraRenderer* GetRenderer() { return m_Renderer; }

		bool IsActive() { return s_ActiveCamera == this; }
		void SetActive() { SetActiveCamera(this); }

		static Camera* GetActiveCamera() { return s_ActiveCamera; }
		static void SetActiveCamera(Camera* camera) { s_ActiveCamera = camera; }

		WV_SERIALIZE_COMPONENT(Camera)
		WV_SERIALIZE_COMPONENT_END

	public:
		Renderer::CameraMode GetCameraMode() { return m_Renderer->GetCameraMode(); }
		float GetOrthoSize() { return m_Renderer->GetOrthoSize(); }
		float GetFieldOfView() { return m_Renderer->GetFieldOfView(); }
		float GetClipNear() { return m_Renderer->GetClipNear(); }
		float GetClipFar() { return m_Renderer->GetClipFar(); }
		glm::mat4 GetProjection() { return m_Renderer->GetProjection(); }
		glm::mat4 GetView() { return m_Renderer->GetView(); }

		void SetCameraMode(Renderer::CameraMode mode) { m_Renderer->SetCameraMode(mode); }
		void SetProjection(float width, float height) { m_Renderer->SetProjection(width, height); }
		void SetOrthoSize(float orthoSize) { m_Renderer->SetOrthoSize(orthoSize); }
		void SetFieldOfView(float fov) { m_Renderer->SetFieldOfView(fov); }
		void SetClipSpaceNear(float near) { m_Renderer->SetClipSpaceNear(near); }
		void SetClipSpaceFar(float far) { m_Renderer->SetClipSpaceFar(far); }

	private:
		Renderer::CameraRenderer* m_Renderer = new Renderer::CameraRenderer();

		static inline Camera* s_ActiveCamera = nullptr;
	};
}