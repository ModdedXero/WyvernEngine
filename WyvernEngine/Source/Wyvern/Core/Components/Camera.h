#pragma once

#include <Wyvern/Core/Scene/Component.h>
#include <Wyvern/Renderer/CameraRenderer.h>

namespace Wyvern
{
	struct Camera : public Component<Camera>
	{
		Vector4 clearColor = { 0.1f, 0.1f, 0.2f, 1.0f };

		Render::CameraRenderer* GetRenderer() { return m_Renderer; }

		bool IsActive() { return m_ActiveCamera; }
		void SetActive() { SetActiveCamera(this); }

		static Camera* GetActiveCamera();
		static void SetActiveCamera(Camera* camera);

	public:
		Render::CameraMode GetCameraMode() { return m_Renderer->GetCameraMode(); }
		float GetOrthoSize() { return m_Renderer->GetOrthoSize(); }
		float GetFieldOfView() { return m_Renderer->GetFieldOfView(); }
		float GetClipNear() { return m_Renderer->GetClipNear(); }
		float GetClipFar() { return m_Renderer->GetClipFar(); }
		glm::mat4 GetProjection() { return m_Renderer->GetProjection(); }
		glm::mat4 GetView() { return m_Renderer->GetView(); }

		void SetCameraMode(Render::CameraMode mode) { m_Renderer->SetCameraMode(mode); }
		void SetProjection(float width, float height) { m_Renderer->SetProjection(width, height); }
		void SetOrthoSize(float orthoSize) { m_Renderer->SetOrthoSize(orthoSize); }
		void SetFieldOfView(float fov) { m_Renderer->SetFieldOfView(fov); }
		void SetClipNear(float near) { m_Renderer->SetClipNear(near); }
		void SetClipFar(float far) { m_Renderer->SetClipFar(far); }

		virtual void DrawEditor() override;
	private:
		Render::CameraRenderer* m_Renderer = new Render::CameraRenderer();
		bool m_ActiveCamera;
	};
}