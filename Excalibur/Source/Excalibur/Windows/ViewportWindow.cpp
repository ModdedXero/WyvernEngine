#include "ViewportWindow.h"

#include <Excalibur/Core/EditorLayer.h>

#include <imgui.h>
#include <ImGuizmo.h>

namespace Merlin::Editor
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
		if (selectedContext)
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

			ImGuizmo::Manipulate(glm::value_ptr(cameraView), glm::value_ptr(cameraProjection),
				ImGuizmo::OPERATION::ROTATE, ImGuizmo::LOCAL, glm::value_ptr(transform));

			if (ImGuizmo::IsUsing())
			{
				glm::vec3 position, rotation, scale;
				Matrix4x4::Decompose(transform, position, rotation, scale);

				glm::vec3 deltaRotation = rotation - transformComp->rotation.glmPosition();
				transformComp->position = position;
				transformComp->rotation += deltaRotation;
				transformComp->scale = scale;
			}
		}
	}
}