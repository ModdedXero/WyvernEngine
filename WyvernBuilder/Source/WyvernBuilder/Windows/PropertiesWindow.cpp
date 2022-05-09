#include "PropertiesWindow.h"

#include <WyvernBuilder/Core/BuilderLayer.h>

#include <imgui.h>
#include <imgui_internal.h>

namespace Wyvern::Editor
{
	void PropertiesWindow::OnGUI()
	{
		if (!Scene::IsEntityValid(BuilderLayer::GetSelectedContext())) 
			BuilderLayer::SetSelectedContext(nullptr);
		if (BuilderLayer::GetSelectedContext() == nullptr) return;

		if (BuilderLayer::GetSelectedContext() != s_SelectedContext)
			s_SelectedContext = BuilderLayer::GetSelectedContext();

		DrawComponents();
	}

	void PropertiesWindow::DrawComponents()
	{
		Tag* tag = s_SelectedContext->GetTag();

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
					auto newComp = component.second(Scene::GetActiveScene(), s_SelectedContext->GetSceneID());
					newComp->AddToEntity(s_SelectedContext);
					ImGui::CloseCurrentPopup();
				}
			}

			ImGui::EndPopup();
		}

		ImGui::PopItemWidth();
		ImGui::Separator();

		DrawComponent("Transform", s_SelectedContext->GetTransform(), s_SelectedContext, true);

		for (Component* component : s_SelectedContext->GetAllComponents())
		{
			DrawComponent(typeid(*component).name(), component, s_SelectedContext);
		}
	}

	void PropertiesWindow::DrawComponent(const std::string label, Component* component, Entity* ent, bool isDefault)
	{
		if (component)
		{
			ImGuiTreeNodeFlags treeNodeFlags =
				ImGuiTreeNodeFlags_DefaultOpen
				| ImGuiTreeNodeFlags_AllowItemOverlap
				| ImGuiTreeNodeFlags_Framed
				| ImGuiTreeNodeFlags_SpanAvailWidth
				| ImGuiTreeNodeFlags_AllowItemOverlap
				| ImGuiTreeNodeFlags_FramePadding;

			ImVec2 contentRegionAvailable = ImGui::GetContentRegionAvail();

			ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2{ 4, 4 });
			float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
			ImGui::Separator();

			size_t pos = label.find_last_of(":");
			bool open = ImGui::TreeNodeEx((void*)typeid(*component).hash_code(), treeNodeFlags, label.substr(pos + 1).c_str());

			ImGui::PopStyleVar();

			ImGui::SameLine(contentRegionAvailable.x - lineHeight * 0.5f);
			if (ImGui::Button("-", ImVec2{ lineHeight, lineHeight }))
				ImGui::OpenPopup("ComponentSettings");

			if (ImGui::BeginPopup("ComponentSettings"))
			{
				if (!isDefault)
				{
					if (ImGui::MenuItem("Remove"))
						Scene::RemoveComponent(ent, component->GetSceneID());
				}

				ImGui::EndPopup();
			}

			if (open)
			{
				component->DrawEditor();
				ImGui::TreePop();
			}
		}
	}
}