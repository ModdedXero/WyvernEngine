#pragma once

#include <Wyvern.h>

#include <imgui.h>
#include <imgui_internal.h>

namespace Wyvern::Editor
{
	class EditorGUIInternal
	{
	public:
		template <typename T, typename UIFunction>
		static void DrawComponent(const std::string label, Entity* entity, UIFunction function);
	};

	template<typename T, typename UIFunction>
	inline void EditorGUIInternal::DrawComponent(const std::string label, Entity* entity, UIFunction uiFunction)
	{
		T* component = entity->GetComponent<T>();
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

			bool open = ImGui::TreeNodeEx((void*)typeid(T).hash_code(), treeNodeFlags, label.c_str());

			ImGui::PopStyleVar();
			ImGui::SameLine(contentRegionAvailable.x - lineHeight * 0.5f);
			if (ImGui::Button("-", ImVec2{lineHeight, lineHeight}))
				ImGui::OpenPopup("ComponentSettings");

			if (ImGui::BeginPopup("ComponentSettings"))
			{
				if (ImGui::MenuItem("Remove"))
					entity->RemoveComponent<T>();

				ImGui::EndPopup();
			}

			if (open)
			{
				uiFunction(component);
				ImGui::TreePop();
			}
		}
	}
}