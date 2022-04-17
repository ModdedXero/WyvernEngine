#include "PropertiesWindow.h"

#include <Excalibur/Core/EditorLayer.h>
#include <Excalibur/Utility/EditorGUI.h>

#include <imgui.h>

namespace Merlin::Editor
{
	void PropertiesWindow::OnGUI()
	{
		if (!Scene::IsEntityValid(EditorLayer::GetSelectedContext())) 
			EditorLayer::SetSelectedContext(nullptr);
		if (EditorLayer::GetSelectedContext() == nullptr) return;

		if (EditorLayer::GetSelectedContext() != m_SelectedContext)
			m_SelectedContext = EditorLayer::GetSelectedContext();

		DrawComponents();

		if (ImGui::Button("Add Component"))
			ImGui::OpenPopup("Add Component");

		if (ImGui::BeginPopup("Add Component"))
		{
			if (ImGui::MenuItem("Camera"))
			{
				m_SelectedContext->AddComponent<Camera>();
				ImGui::CloseCurrentPopup();
			}

			if (ImGui::MenuItem("Sprite Renderer"))
			{
				m_SelectedContext->AddComponent<SpriteRenderer>();
				ImGui::CloseCurrentPopup();
			}

			ImGui::EndPopup();
		}
	}

	void PropertiesWindow::DrawComponents()
	{
		Tag* tag = m_SelectedContext->GetTag();

		char buffer[256];
		memset(buffer, 0, sizeof(buffer));
		strcpy_s(buffer, sizeof(buffer), tag->name.c_str());

		if (ImGui::InputText("Name", buffer, sizeof(buffer)))
		{
			tag->name = std::string(buffer);
		}

		ImGui::Separator();

		Transform* transform = m_SelectedContext->GetTransform();

		if (ImGui::TreeNodeEx((void*)m_SelectedContext->GetID(), ImGuiTreeNodeFlags_DefaultOpen, "Transform"))
		{
			EditorGUI::Vector3Control("Position", transform->position);
			EditorGUI::Vector3Control("Rotation", transform->rotation);
			EditorGUI::Vector3Control("Scale", transform->scale, 1.0f);

			ImGui::TreePop();
		}

		ImGui::Separator();

		Camera* camera = m_SelectedContext->GetComponent<Camera>();
		if (camera)
		{
			if (ImGui::TreeNodeEx((void*)m_SelectedContext->GetID(), ImGuiTreeNodeFlags_DefaultOpen, "Camera"))
			{
				const char* projectionTypeStrings[] = { "Perspective", "Orthographic" };
				const char* currentProjectionString = projectionTypeStrings[(int)camera->GetCameraMode()];

				if (ImGui::BeginCombo("Projection", currentProjectionString))
				{
					for (int i = 0; i < 2; i++)
					{
						bool isSelected = currentProjectionString == projectionTypeStrings[i];
						if (ImGui::Selectable(projectionTypeStrings[i], isSelected))
						{
							currentProjectionString = projectionTypeStrings[i];
							camera->SetCameraMode((CameraMode)i);
						}
					}

					ImGui::EndCombo();
				}

				if (camera->GetCameraMode() == CameraMode::Perspective)
				{
					float fov = camera->GetFieldOfView();
					if (ImGui::DragFloat("FOV", &fov, 1))
						camera->SetFieldOfView(fov);
				}
				else
				{
					float orthoSize = camera->GetOrthoSize();
					if (ImGui::DragFloat("Ortho Size", &orthoSize, 0.1f))
						camera->SetOrthoSize(orthoSize);
				}

				float near = camera->GetClipNear();
				if (ImGui::DragFloat("Clip Near", &near, 0.1f))
					camera->SetClipSpaceNear(near);

				float far = camera->GetClipFar();
				if (ImGui::DragFloat("Clip Far", &far, 0.1f))
					camera->SetClipSpaceFar(far);

				ImGui::TreePop();
			}
		}
	}
}