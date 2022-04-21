#include "PropertiesWindow.h"

#include <Excalibur/Core/EditorLayer.h>
#include <Excalibur/Utility/EditorGUI.h>
#include <Excalibur/Utility/EditorGUIInternal.h>

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
	}

	void PropertiesWindow::DrawComponents()
	{
		Tag* tag = m_SelectedContext->GetTag();

		char buffer[256];
		memset(buffer, 0, sizeof(buffer));
		strcpy_s(buffer, sizeof(buffer), tag->name.c_str());

		if (ImGui::InputText("##Tag", buffer, sizeof(buffer)))
		{
			tag->name = std::string(buffer);
		}

		ImGui::SameLine();
		ImGui::PushItemWidth(-1);

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

		ImGui::PopItemWidth();
		ImGui::Separator();

		EditorGUIInternal::DrawComponent<Transform>("Transform", m_SelectedContext, [](auto& component)
			{
				EditorGUI::Vector3Control("Position", component->position);
				EditorGUI::Vector3Control("Rotation", component->rotation);
				EditorGUI::Vector3Control("Scale", component->scale, 1.0f);
			});

		EditorGUIInternal::DrawComponent<Camera>("Camera", m_SelectedContext, [](auto& component)
			{
				const char* projectionTypeStrings[] = { "Perspective", "Orthographic" };
				const char* currentProjectionString = projectionTypeStrings[(int)component->GetCameraMode()];

				if (ImGui::BeginCombo("Projection", currentProjectionString))
				{
					for (int i = 0; i < 2; i++)
					{
						bool isSelected = currentProjectionString == projectionTypeStrings[i];
						if (ImGui::Selectable(projectionTypeStrings[i], isSelected))
						{
							currentProjectionString = projectionTypeStrings[i];
							component->SetCameraMode((CameraMode)i);
						}
					}

					ImGui::EndCombo();
				}

				if (component->GetCameraMode() == CameraMode::Perspective)
				{
					float fov = component->GetFieldOfView();
					if (ImGui::DragFloat("FOV", &fov, 1))
						component->SetFieldOfView(fov);
				}
				else
				{
					float orthoSize = component->GetOrthoSize();
					if (ImGui::DragFloat("Ortho Size", &orthoSize, 0.1f))
						component->SetOrthoSize(orthoSize);
				}

				float near = component->GetClipNear();
				if (ImGui::DragFloat("Clip Near", &near, 0.1f))
					component->SetClipSpaceNear(near);

				float far = component->GetClipFar();
				if (ImGui::DragFloat("Clip Far", &far, 0.1f))
					component->SetClipSpaceFar(far);
			});

		EditorGUIInternal::DrawComponent<SpriteRenderer>("Sprite Renderer", m_SelectedContext, [](auto& component)
			{
				EditorGUI::Color4Control("Color", component->color);
			});
	}
}