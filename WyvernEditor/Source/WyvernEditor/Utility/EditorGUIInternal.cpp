#include "EditorGUIInternal.h"


#include <imgui.h>
#include <imgui_internal.h>

namespace Wyvern::Editor
{
    void EditorGUIInternal::DrawComponent(const std::string label, Component* component, Entity* ent, bool isDefault)
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