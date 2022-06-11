#include <Wyvern.h>
#include <WyvernEditor.h>

#include <imgui.h>
#include <imgui_internal.h>

namespace Wyvern
{
	void Material::_DrawProperties()
	{
		std::string materialPath = m_MaterialPath.Filename();
		Editor::EditorGUI::TextControl("Material: ", materialPath, true);

		std::string path = m_ShaderPath;
		Editor::EditorGUI::TextControl("Shader: ", path, true);
	}

	void Entity::_DrawProperties()
	{
		if (!IsValid()) return;

		ImGui::BeginGroup();
		ImGui::BeginChild("component view", ImVec2(0, -ImGui::GetFrameHeightWithSpacing()));

		bool isActive = IsActive();
		Editor::EditorGUI::BoolControl("Active", isActive);
		SetActive(isActive);

		ImGui::SameLine();
		ImGui::PushItemWidth(-1);

		Tag* tag = GetTag();

		char buffer[256];
		memset(buffer, 0, sizeof(buffer));
		strcpy_s(buffer, sizeof(buffer), tag->name.c_str());

		if (ImGui::InputText("##Tag", buffer, sizeof(buffer)))
		{
			tag->name = std::string(buffer);
		}

		ImGui::PopItemWidth();

		for (ComponentBase* component : GetComponents())
		{
			if (typeid(*component).name() == std::string(typeid(Tag).name()))
				continue;

			Editor::EditorGUIInternal::DrawComponent(typeid(*component).name(), component, *this);
		}

		ImGui::EndChild();

		if (ImGui::Button("Add Component", ImVec2(ImGui::GetContentRegionAvail().x, Editor::EditorInfo::LineHeight())))
			ImGui::OpenPopup("Add Component");

		if (ImGui::BeginPopup("Add Component"))
		{
			for (auto& component : ApplicationDomain::GetComponents())
			{
				if (component.first == "Tag" || component.first == "Transform")
					continue;

				if (ImGui::MenuItem(component.first.c_str()))
				{
					auto newComp = component.second(Scene::GetActiveScene(), GetSceneID());
					ImGui::CloseCurrentPopup();
				}
			}

			ImGui::EndPopup();
		}

		ImGui::EndGroup();
	}
}