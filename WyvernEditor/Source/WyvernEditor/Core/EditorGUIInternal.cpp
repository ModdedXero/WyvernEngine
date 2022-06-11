#include "EditorGUIInternal.h"

#include <Wyvern/Tools/FileSystem.h>
#include <Wyvern/Core/Scene/Entity.h>
#include <Wyvern/Core/Scene/Component.h>

#include <imgui.h>
#include <imgui_internal.h>
#include <iostream>
#include <string>

namespace Wyvern::Editor
{
	void EditorGUIInternal::DragDropSource(DragDropTypes returnType, const void* target, size_t size)
	{
		if (ImGui::BeginDragDropSource())
		{
			if (returnType == DragDropTypes::FileSystem)
				ImGui::SetDragDropPayload("FILESYSTEM_TARGET", target, size, ImGuiCond_Once);
			else if (returnType == DragDropTypes::Entity)
				ImGui::SetDragDropPayload("ENTITY_TARGET", target, size, ImGuiCond_Once);

			ImGui::EndDragDropSource();
		}
	}

	void EditorGUIInternal::DrawComponent(const std::string label, ComponentBase* component, Entity ent, bool isDefault)
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

			ImGui::SameLine(contentRegionAvailable.x - lineHeight);
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
				ImGui::Unindent(10.0f);

				component->DrawEditor();

				ImGui::Indent(10.0f);
				ImGui::TreePop();
			}
		}
	}
}