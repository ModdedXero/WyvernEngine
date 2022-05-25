#include "EditorGUI.h"
#include "EditorGUIInternal.h"
#include "EditorInfo.h"

#include <Wyvern/Core/Math/Vector.h>
#include <Wyvern/Core/Scene/Entity.h>
#include <Wyvern/Core/Components/Tag.h>
#include <Wyvern/Utils/FileSystem.h>

#include <imgui.h>
#include <imgui_internal.h>

namespace Wyvern::Editor
{
	void EditorGUI::Label(const std::string& label)
	{
		ImGui::SetCursorPosY(EditorInfo::TextPadding());
		ImGui::Text(label.c_str());
	}

	void EditorGUI::Vector2Control(const std::string& label, Vector2& values, float resetValue, float columnWidth)
	{
		ImGuiIO& io = ImGui::GetIO();
		auto boldFont = io.Fonts->Fonts[0];

		ImGui::PushID(label.c_str());

		ImGui::Columns(2, 0, false);
		ImGui::SetColumnWidth(0, columnWidth);
		EditorGUI::Label(label);
		ImGui::NextColumn();

		ImGui::PushMultiItemsWidths(2, ImGui::CalcItemWidth());
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 0 });

		float lineHeight = EditorInfo::LineHeight();
		ImVec2 buttonSize = { lineHeight + 3.0f, lineHeight };

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.8f, 0.1f, 0.15f, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.8f, 0.2f, 0.2f, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.8f, 0.1f, 0.15f, 1.0f));
		ImGui::PushFont(boldFont);
		if (ImGui::Button("X", buttonSize))
			values.x = resetValue;
		ImGui::PopFont();
		ImGui::PopStyleColor(3);

		ImGui::SameLine();
		ImGui::DragFloat("##X", &values.x, 0.1f);
		ImGui::PopItemWidth();
		ImGui::SameLine();

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.2f, 0.7f, 0.2f, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.3f, 0.8f, 0.3f, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.2f, 0.7f, 0.2f, 1.0f));
		ImGui::PushFont(boldFont);
		if (ImGui::Button("Y", buttonSize))
			values.y = resetValue;
		ImGui::PopFont();
		ImGui::PopStyleColor(3);

		ImGui::SameLine();
		ImGui::DragFloat("##Y", &values.y, 0.1f);
		ImGui::PopItemWidth();

		ImGui::PopStyleVar();

		ImGui::Columns(1);
		ImGui::PopID();
	}

	void EditorGUI::Vector3Control(const std::string& label, Vector3& values, float resetValue, float columnWidth)
	{
		ImGuiIO& io = ImGui::GetIO();
		auto boldFont = io.Fonts->Fonts[0];

		ImGui::PushID(label.c_str());

		ImGui::Columns(2, 0, false);
		ImGui::SetColumnWidth(0, columnWidth);
		EditorGUI::Label(label);
		ImGui::NextColumn();

		ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 0 });

		float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
		ImVec2 buttonSize = { lineHeight + 3.0f, lineHeight };

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.8f, 0.1f, 0.15f, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.8f, 0.2f, 0.2f, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.8f, 0.1f, 0.15f, 1.0f));
		ImGui::PushFont(boldFont);
		if (ImGui::Button("X", buttonSize))
			values.x = resetValue;
		ImGui::PopFont();
		ImGui::PopStyleColor(3);

		ImGui::SameLine();
		ImGui::DragFloat("##X", &values.x, 0.1f);
		ImGui::PopItemWidth();
		ImGui::SameLine();

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.2f, 0.7f, 0.2f, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.3f, 0.8f, 0.3f, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.2f, 0.7f, 0.2f, 1.0f));
		ImGui::PushFont(boldFont);
		if (ImGui::Button("Y", buttonSize))
			values.y = resetValue;
		ImGui::PopFont();
		ImGui::PopStyleColor(3);

		ImGui::SameLine();
		ImGui::DragFloat("##Y", &values.y, 0.1f);
		ImGui::PopItemWidth();
		ImGui::SameLine();

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.1f, 0.25f, 0.8f, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.2f, 0.35f, 0.9f, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.1f, 0.25f, 0.8f, 1.0f));
		ImGui::PushFont(boldFont);
		if (ImGui::Button("Z", buttonSize))
			values.z = resetValue;
		ImGui::PopFont();
		ImGui::PopStyleColor(3);

		ImGui::SameLine();
		ImGui::DragFloat("##Z", &values.z, 0.1f);
		ImGui::PopItemWidth();

		ImGui::PopStyleVar();

		ImGui::Columns(1);
		ImGui::PopID();
	}

	void EditorGUI::Vector4Control(const std::string& label, Vector4& values, float resetValue, float columnWidth)
	{
		ImGui::PushID(label.c_str());

		ImGui::Columns(2, 0, false);
		ImGui::SetColumnWidth(0, columnWidth);
		EditorGUI::Label(label);
		ImGui::NextColumn();

		ImGui::PushMultiItemsWidths(4, ImGui::CalcItemWidth());
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 0 });

		float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
		ImVec2 buttonSize = { lineHeight + 3.0f, lineHeight };

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.8f, 0.1f, 0.15f, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.8f, 0.2f, 0.2f, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.8f, 0.1f, 0.15f, 1.0f));
		if (ImGui::Button("X", buttonSize))
			values.x = resetValue;
		ImGui::PopStyleColor(3);

		ImGui::SameLine();
		ImGui::DragFloat("##X", &values.x, 0.1f);
		ImGui::PopItemWidth();
		ImGui::SameLine();

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.2f, 0.7f, 0.2f, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.3f, 0.8f, 0.3f, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.2f, 0.7f, 0.2f, 1.0f));
		if (ImGui::Button("Y", buttonSize))
			values.y = resetValue;
		ImGui::PopStyleColor(3);

		ImGui::SameLine();
		ImGui::DragFloat("##Y", &values.y, 0.1f);
		ImGui::PopItemWidth();
		ImGui::SameLine();

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.1f, 0.25f, 0.8f, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.2f, 0.35f, 0.9f, 1.0f));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.1f, 0.25f, 0.8f, 1.0f));
		if (ImGui::Button("Z", buttonSize))
			values.z = resetValue;
		ImGui::PopStyleColor(3);

		ImGui::SameLine();
		ImGui::DragFloat("##Z", &values.z, 0.1f);
		ImGui::PopItemWidth();
		ImGui::SameLine();

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1.0f, 1.0f, 1.0f, 0.6f));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(1.0f, 1.0f, 1.0f, 0.8f));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(1.0f, 1.0f, 1.0f, 0.6f));
		if (ImGui::Button("W", buttonSize))
			values.w = resetValue;
		ImGui::PopStyleColor(3);

		ImGui::SameLine();
		ImGui::DragFloat("##W", &values.w, 0.1f);
		ImGui::PopItemWidth();

		ImGui::PopStyleVar();

		ImGui::Columns(1);
		ImGui::PopID();
	}

	void EditorGUI::Color4Control(const std::string& label, Vector4& values, float columnWidth)
	{
		ImGui::Columns(2, 0, false);
		ImGui::SetColumnWidth(0, columnWidth);
		EditorGUI::Label(label);
		ImGui::NextColumn();

		float* fValues[4] =
		{
			&values.x,
			&values.y,
			&values.z,
			&values.w
		};

		std::string id = "##" + label;
		ImGui::ColorEdit4(id.c_str(), *fValues);

		ImGui::Columns(1);
	}

	void EditorGUI::FloatControl(const std::string& label, float& value, float columnWidth)
	{
		ImGui::Columns(2, 0, false);
		ImGui::SetColumnWidth(0, columnWidth);
		EditorGUI::Label(label);
		ImGui::NextColumn();

		std::string id = "##" + label;
		ImGui::DragFloat(id.c_str(), &value);

		ImGui::Columns(1);
	}

	void EditorGUI::IntControl(const std::string& label, int& value, float columnWidth)
	{
		ImGui::Columns(2, 0, false);
		ImGui::SetColumnWidth(0, columnWidth);
		EditorGUI::Label(label);
		ImGui::NextColumn();

		std::string id = "##" + label;
		ImGui::DragInt(id.c_str(), &value);

		ImGui::Columns(1);
	}

	void EditorGUI::BoolControl(const std::string& label, bool& value, float columnWidth)
	{
		ImGui::Columns(2, 0, false);
		ImGui::SetColumnWidth(0, columnWidth);
		EditorGUI::Label(label);
		ImGui::NextColumn();

		std::string id = "##" + label;
		ImGui::Checkbox(id.c_str(), &value);

		ImGui::Columns(1);
	}

	void EditorGUI::ComboControl(const std::string& label, const char* values[], int& valueIndex, int arraySize, float columnWidth)
	{
		ImGui::Columns(2, 0, false);
		ImGui::SetColumnWidth(0, columnWidth);
		EditorGUI::Label(label);
		ImGui::NextColumn();

		std::string id = "##" + label;
		if (ImGui::BeginCombo(id.c_str(), values[valueIndex]))
		{
			for (int i = 0; i < arraySize; i++)
			{
				bool isSelected = (values[valueIndex] == values[i]);
				if (ImGui::Selectable(values[i], isSelected))
					valueIndex = i;
				if (isSelected)
					ImGui::SetItemDefaultFocus();
			}

			ImGui::EndCombo();
		}

		ImGui::Columns(1);
	}

	void EditorGUI::EntityControl(const std::string& label, Entity& entity, float columnWidth)
	{
		ImGui::Columns(2, 0, false);
		ImGui::SetColumnWidth(0, columnWidth);
		EditorGUI::Label(label);
		ImGui::NextColumn();

		float lineHeight = EditorInfo::LineHeight();
		ImGui::Button(label.c_str(), ImVec2{ImGui::GetContentRegionAvail().x, lineHeight});

		std::string targetName = Scene::IsEntityValid(entity) ? entity.GetTag()->name : "None";
		EditorGUIInternal::DragDropTarget(DragDropTypes::Entity, entity);

		if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(0))
		{
			entity = Entity();
		}

		ImGui::Columns(1);
	}

	void EditorGUI::FileSystemControl(const std::string& label, Utils::FileSystem& file, float columnWidth)
	{
		ImGui::Columns(2, 0, false);
		ImGui::SetColumnWidth(0, columnWidth);
		EditorGUI::Label(label);
		ImGui::NextColumn();

		float lineHeight = EditorInfo::LineHeight();
		ImGui::Button(label.c_str(), ImVec2{ImGui::GetContentRegionAvail().x, lineHeight});

		std::string targetName = !file.Filename().empty() ? file.Filename() : "None";
		EditorGUIInternal::DragDropTarget(DragDropTypes::FileSystem, file);

		ImGui::Columns(1);
	}
}