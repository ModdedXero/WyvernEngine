#include "PropertiesWindow.h"

#include <WyvernEditor/Core/EditorLayer.h>
#include <WyvernEditor/Utility/EditorGUI.h>
#include <WyvernEditor/Utility/EditorGUIInternal.h>

#include <imgui.h>

namespace Wyvern::Editor
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
			for (auto& component : ApplicationDomain::GetComponents())
			{
				if (component.first == "Tag" || component.first == "Transform")
					continue;

				if (ImGui::MenuItem(component.first.c_str()))
				{
					auto newComp = component.second(m_SelectedContext->GetID());
					newComp->AddToEntity(m_SelectedContext);
					ImGui::CloseCurrentPopup();
				}
			}

			ImGui::EndPopup();
		}

		ImGui::PopItemWidth();
		ImGui::Separator();

		EditorGUIInternal::DrawComponent("Transform", m_SelectedContext->GetTransform(), m_SelectedContext, true);

		for (Component* component : m_SelectedContext->GetAllComponents())
		{
			EditorGUIInternal::DrawComponent(typeid(*component).name(), component, m_SelectedContext);
		}
	}
}