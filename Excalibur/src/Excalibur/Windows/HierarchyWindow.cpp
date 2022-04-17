#include "HierarchyWindow.h"

#include <Excalibur/Core/EditorLayer.h>

#include <imgui.h>

namespace Merlin::Editor
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
			EditorLayer::SetSelectedContext(nullptr);
		}

		for (Entity* ent : EntityList<>())
		{
			if (ent->GetEditorOnly()) continue;
			DrawEntityNode(ent);
		}

		// Right click menu
		if (ImGui::BeginPopupContextWindow(0, 1, false))
		{
			if (ImGui::MenuItem("Empty Entity"))
				Scene::CreateEntity<Entity>();

			ImGui::EndPopup();
		}
	}

	void HierarchyWindow::DrawEntityNode(Entity* ent, bool isChild)
	{
		if (!isChild && ent->GetParent() != nullptr) return;

		Tag* tag = ent->GetTag();

		ImGuiTreeNodeFlags flags = ((EditorLayer::GetSelectedContext() == ent) ? ImGuiTreeNodeFlags_Selected : 0) | ((ent->GetChildren().size() > 0) ? ImGuiTreeNodeFlags_OpenOnArrow : ImGuiTreeNodeFlags_Leaf);
		bool opened = ImGui::TreeNodeEx((void*)ent->GetID(), flags, tag->name.c_str());
		if (ImGui::IsItemClicked())
		{
			EditorLayer::SetSelectedContext(ent);
		}

		bool entityDeleted = false;
		if (ImGui::BeginPopupContextItem())
		{
			if (ImGui::MenuItem("Delete Entity"))
				entityDeleted = true;

			ImGui::EndPopup();
		}

		if (opened)
		{
			DrawEntityChildren(ent);
			ImGui::TreePop();
		}

		if (entityDeleted)
			ent->DestroyEntity();
	}

	void HierarchyWindow::DrawEntityChildren(Entity* ent)
	{
		for (Entity* ent : ent->GetChildren())
		{
			DrawEntityNode(ent, true);
		}
	}
}