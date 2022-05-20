#include "HierarchyWindow.h"

#include <WyvernBuilder/Core/BuilderLayer.h>

#include <imgui.h>

namespace Wyvern
{
	struct EntityNode
	{
		Entity* Ent;
		ImGuiTreeNodeFlags Flags;
	};

	void HierarchyWindow::OnGUI()
	{
		if (Input::IsMouseButton(0) && IsHovered())
		{
			BuilderLayer::SetSelectedContext(nullptr);
		}

		for (Entity* ent : EntityList<>(Scene::GetActiveScene()))
		{
			DrawEntityNode(ent);
		}

		// Right click menu
		if (ImGui::BeginPopupContextWindow("Empty", ImGuiPopupFlags_NoOpenOverItems | ImGuiPopupFlags_MouseButtonRight))
		{
			if (ImGui::MenuItem("Empty Entity"))
				Scene::CreateEntity(Scene::GetActiveScene());

			ImGui::EndPopup();
		}
	}

	void HierarchyWindow::DrawEntityNode(Entity* ent, bool isChild)
	{
		if (!isChild && ent->GetParent() != nullptr) return;

		Tag* tag = ent->GetTag();

		ImGuiTreeNodeFlags flags = ((BuilderLayer::GetSelectedContext() == ent) ? ImGuiTreeNodeFlags_Selected : 0); 
		flags |= ((ent->GetChildren().size() > 0) ? ImGuiTreeNodeFlags_OpenOnArrow : ImGuiTreeNodeFlags_Leaf);
		flags |= ImGuiTreeNodeFlags_SpanAvailWidth;

		bool opened = ImGui::TreeNodeEx((void*)ent->GetSceneID(), flags, tag->name.c_str());
		if (ImGui::IsItemClicked())
		{
			BuilderLayer::SetSelectedContext(ent);
		}

		if (ImGui::BeginPopupContextItem(0, ImGuiPopupFlags_NoOpenOverExistingPopup | ImGuiPopupFlags_MouseButtonRight))
		{
			BuilderLayer::SetSelectedContext(ent);

			if (ImGui::MenuItem("Duplicate Entity"))
				Scene::DuplicateEntity(ent);

			if (ImGui::MenuItem("Create Child Entity"))
				ent->AddChildEntity(Scene::CreateEntity(Scene::GetActiveScene()));

			if (ImGui::MenuItem("Delete Entity"))
				ent->DestroyEntity();

			ImGui::EndPopup();
		}

		if (opened)
		{
			DrawEntityChildren(ent);
			ImGui::TreePop();
		}
	}

	void HierarchyWindow::DrawEntityChildren(Entity* ent)
	{
		for (Entity* ent : ent->GetChildren())
		{
			DrawEntityNode(ent, true);
		}
	}
}