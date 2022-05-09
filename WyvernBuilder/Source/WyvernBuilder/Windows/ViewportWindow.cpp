#include "ViewportWindow.h"

#include <WyvernBuilder/Core/BuilderLayer.h>

#include <imgui.h>
#include <ImGuizmo.h>

namespace Wyvern::Editor
{
	void ViewportWindow::OnAttach()
	{
		Renderer::FrameBufferSpecs fbSpec;
		fbSpec.Width = 1280;
		fbSpec.Height = 720;
		m_Framebuffer = new Renderer::Framebuffer(fbSpec);
	}

	void ViewportWindow::OnGUI()
	{
		if (IsFocused() && IsHovered())
			BuilderLayer::GetEditorCamera()->MoveCamera();

		Vector2 windowPanelSize = GetWindowSize();
		if (WindowSize != windowPanelSize)
		{
			m_Framebuffer->Resize(windowPanelSize);
			WindowSize = windowPanelSize;

			BuilderLayer::GetEditorCamera()->Resize(windowPanelSize.x, windowPanelSize.y);
			if (Camera::GetActiveCamera())
				Camera::GetActiveCamera()->GetRenderer()->ResizeView(windowPanelSize.x, windowPanelSize.y);
		}

		unsigned int textureID = m_Framebuffer->GetColorAttachmentRendererID();
		ImGui::Image((void*)textureID, ImVec2{ WindowSize.x, WindowSize.y });

		// Gizmos

		Entity* selectedContext = BuilderLayer::GetSelectedContext();
		if (selectedContext && m_GizmoSelection != -1)
		{
			ImGuizmo::SetOrthographic(false);
			ImGuizmo::SetDrawlist();

			float windowWidth = (float)ImGui::GetWindowWidth();
			float windowHeight = (float)ImGui::GetWindowHeight();
			ImGuizmo::SetRect(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y, windowWidth, windowHeight);

			ViewportCamera* camera = BuilderLayer::GetEditorCamera();
			Transform cameraTransform = *camera->transform;
			cameraTransform.position.y = -cameraTransform.position.y;
			glm::mat4 cameraView = Matrix4x4::Inverse(cameraTransform.GetTransform()).GetNativeMatrix();
			glm::mat4 cameraProjection = camera->GetProjection();

			Transform* transformComp = selectedContext->GetTransform();
			glm::mat4 transform = transformComp->GetTransform().GetNativeMatrix();

			float snapValues[3] = { m_SnapValue, m_SnapValue, m_SnapValue };
			if ((ImGuizmo::OPERATION)m_GizmoSelection == ImGuizmo::OPERATION::ROTATE)
			{
				snapValues[0] = 45.0f;
				snapValues[1] = 45.0f;
				snapValues[2] = 45.0f;
			}

			if (camera->GetCameraMode() == Renderer::CameraMode::Orthographic)
				ImGuizmo::SetOrthographic(true);
			else
				ImGuizmo::SetOrthographic(false);

			ImGuizmo::Manipulate(glm::value_ptr(cameraView), glm::value_ptr(cameraProjection),
				(ImGuizmo::OPERATION)m_GizmoSelection, ImGuizmo::LOCAL, glm::value_ptr(transform),
				nullptr, m_IsSnap ? snapValues : nullptr);

			if (ImGuizmo::IsUsing())
			{
				glm::vec3 position, rotation, scale;
				Matrix4x4::Decompose(transform, position, rotation, scale);

				glm::vec3 deltaRotation = glm::degrees(rotation) - transformComp->rotation.glmPosition();

				if (camera->GetCameraMode() == Renderer::CameraMode::Orthographic)
				{
					transformComp->position.x = position.x;
					transformComp->position.y = position.y;
				}
				else
					transformComp->position = position;
				transformComp->rotation += deltaRotation;
				transformComp->scale = scale;
			}
		}
	}

	void ViewportWindow::OnPreRender()
	{
		m_Framebuffer->Bind();
	}

	void ViewportWindow::OnPostRender()
	{
		m_Framebuffer->Unbind();
	}

	void ViewportWindow::OnEvent(Events::Event& e)
	{
		Events::EventDispatcher dispatch(e);

		dispatch.Distpatch<Events::KeyPressedEvent>(BIND_EVENT_FN(OnKeyPressedEvent));
		dispatch.Distpatch<Events::KeyReleasedEvent>(BIND_EVENT_FN(OnKeyReleasedEvent));
	}

	bool ViewportWindow::OnKeyPressedEvent(Events::KeyPressedEvent& e)
	{
		if (e.GetKeyCode() == KeyCode::Q)
		{
			m_GizmoSelection = -1;
		}

		if (e.GetKeyCode() == KeyCode::W)
		{
			m_GizmoSelection = 0;
		}

		if (e.GetKeyCode() == KeyCode::E)
		{
			m_GizmoSelection = 2;
		}

		if (e.GetKeyCode() == KeyCode::R)
		{
			m_GizmoSelection = 1;
		}

		if (e.GetKeyCode() == KeyCode::LeftControl)
		{
			m_IsSnap = true;
		}

		return true;
	}

	bool ViewportWindow::OnKeyReleasedEvent(Events::KeyReleasedEvent& e)
	{
		if (e.GetKeyCode() == KeyCode::LeftControl)
		{
			m_IsSnap = false;
		}

		return true;
	}
}