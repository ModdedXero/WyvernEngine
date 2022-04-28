#include "ViewportWindow.h"

#include <WyvernEditor/Core/EditorLayer.h>

#include <imgui.h>
#include <ImGuizmo.h>

namespace Wyvern::Editor
{
	void ViewportWindow::OnGUI()
	{
		if (IsFocused() && IsHovered())
			EditorLayer::GetEditorCamera()->MoveCamera();

		Vector2 windowPanelSize = GetWindowSize();
		if (WindowSize != windowPanelSize)
		{
			Renderer::Renderer2D::Framebuffer->Resize(windowPanelSize);
			WindowSize = windowPanelSize;

			EditorLayer::GetEditorCamera()->Resize(windowPanelSize.x, windowPanelSize.y);
		}

		unsigned int textureID = Renderer::Renderer2D::Framebuffer->GetColorAttachmentRendererID();
		ImGui::Image((void*)textureID, ImVec2{ WindowSize.x, WindowSize.y });

		// Gizmos

		Entity* selectedContext = EditorLayer::GetSelectedContext();
		if (selectedContext && m_GizmoSelection != -1)
		{
			ImGuizmo::SetOrthographic(false);
			ImGuizmo::SetDrawlist();

			float windowWidth = (float)ImGui::GetWindowWidth();
			float windowHeight = (float)ImGui::GetWindowHeight();
			ImGuizmo::SetRect(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y, windowWidth, windowHeight);

			ViewportCamera* camera = EditorLayer::GetEditorCamera();
			glm::mat4 cameraView = Matrix4x4::Inverse(camera->transform->GetTransform()).GetNativeMatrix();
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

			ImGuizmo::Manipulate(glm::value_ptr(cameraView), glm::value_ptr(cameraProjection),
				(ImGuizmo::OPERATION)m_GizmoSelection, ImGuizmo::LOCAL, glm::value_ptr(transform),
				nullptr, m_IsSnap ? snapValues : nullptr);

			if (ImGuizmo::IsUsing())
			{
				glm::vec3 position, rotation, scale;
				Matrix4x4::Decompose(transform, position, rotation, scale);

				glm::vec3 deltaRotation = glm::degrees(rotation) - transformComp->rotation.glmPosition();
				transformComp->position = position;
				transformComp->rotation += deltaRotation;
				transformComp->scale = scale;
			}
		}
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