#include "ViewportWindow.h"

#include <WyvernBuilder/Core/BuilderLayer.h>

#include <imgui.h>
#include <ImGuizmo.h>

namespace Wyvern
{
	void ViewportWindow::OnAttach()
	{
		m_Framebuffer = Render::Renderer::GetFramebuffer();
	}

	void ViewportWindow::OnGUI()
	{
		if (IsFocused() && Scene::GetActiveScene()->GetSceneState() != SceneState::Play)
			BuilderLayer::GetViewportCamera()->MoveCamera();

		Vector2 windowPanelSize = GetWindowSize();
		m_Framebuffer->Resize(windowPanelSize);

		unsigned int textureID = m_Framebuffer->GetColorAttachmentRendererID();
		ImGui::Image((void*)textureID, ImVec2{ (float)m_Framebuffer->GetSpecification().Width, (float)m_Framebuffer->GetSpecification().Height }, ImVec2{0, 1}, ImVec2{1, 0});

		m_Framebuffer->Bind();
		if (IsHovered())
		{
			int index = m_Framebuffer->ReadPixel(1, GetCursorPosition().x, GetCursorPosition().y);
			Entity ent = Scene::GetEntity(Scene::GetActiveScene(), index);
			m_HoverEntity = ent;
		}
		m_Framebuffer->Unbind();

		Tools::FileSystem pathPtr;
		EditorGUIInternal::DragDropTarget(DragDropTypes::FileSystem, pathPtr);
		if (pathPtr.IsExtension(".wyvern")) BuilderLayer::LoadScene(pathPtr);

		// Gizmos

		Entity* selectedContext = BuilderLayer::GetSelectedContext<Entity>();
		if (selectedContext && selectedContext->IsValid() && m_GizmoSelection != -1 && Scene::GetActiveScene()->GetSceneState() == SceneState::Edit)
		{
			ViewportCamera* camera = BuilderLayer::GetViewportCamera();

			if (camera->GetCameraMode() == Render::CameraMode::Orthographic)
				ImGuizmo::SetOrthographic(true);
			else
				ImGuizmo::SetOrthographic(false);
			ImGuizmo::SetDrawlist();

			float windowWidth = (float)ImGui::GetWindowWidth();
			float windowHeight = (float)ImGui::GetWindowHeight();
			ImGuizmo::SetRect(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y, windowWidth, windowHeight);

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

			ImGuizmo::Manipulate(glm::value_ptr(cameraView), glm::value_ptr(cameraProjection),
				(ImGuizmo::OPERATION)m_GizmoSelection, ImGuizmo::LOCAL, glm::value_ptr(transform),
				nullptr, m_IsSnap ? snapValues : nullptr);

			if (ImGuizmo::IsUsing())
			{
				glm::vec3 position, rotation, scale;
				Matrix4x4::Decompose(transform, position, rotation, scale);

				glm::vec3 deltaRotation = glm::degrees(rotation) - (glm::vec3)transformComp->rotation;

				if (camera->GetCameraMode() == Render::CameraMode::Orthographic)
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

	void ViewportWindow::OnEvent(Events::Event& e)
	{
		Events::EventDispatcher dispatch(e);

		dispatch.Distpatch<Events::KeyPressedEvent>(BIND_EVENT_FN(OnKeyPressedEvent));
		dispatch.Distpatch<Events::KeyReleasedEvent>(BIND_EVENT_FN(OnKeyReleasedEvent));
		dispatch.Distpatch<Events::MouseButtonPressedEvent>(BIND_EVENT_FN(OnMouseButtonPressed));
		dispatch.Distpatch<Events::MouseScrolledEvent>(BIND_EVENT_FN(OnMouseScrolledEvent));
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

	bool ViewportWindow::OnMouseButtonPressed(Events::MouseButtonPressedEvent& e)
	{
		if (e.GetKey() == MouseCode::MOUSE_BUTTON_LEFT)
		{
			if (IsHovered() && !ImGuizmo::IsOver())
			{
				Entity* ent = new Entity(m_HoverEntity);
				BuilderLayer::SetSelectedContext(ent);
			}
		}

		return true;
	}

	bool ViewportWindow::OnMouseScrolledEvent(Events::MouseScrolledEvent& e)
	{
		BuilderLayer::GetViewportCamera()->OnScroll(e);

		return true;
	}
}