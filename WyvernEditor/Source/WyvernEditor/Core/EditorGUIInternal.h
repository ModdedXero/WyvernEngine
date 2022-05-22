#pragma once

#include "EditorInfo.h"

namespace Wyvern::Editor
{
	enum class DragDropTypes
	{
		FileSystem,
		Entity
	};

	class EditorGUIInternal
	{
	public:
		template <typename Target>
		static void DragDropTarget(const char* label, DragDropTypes returnType, Target& target);
		static void DragDropSource(DragDropTypes returnType, const void* target, size_t size);
	};

	template <typename Target>
	inline void EditorGUIInternal::DragDropTarget(const char* label, DragDropTypes returnType, Target& target)
	{
		float lineHeight = EditorInfo::LineHeight();
		ImGui::Button(label, ImVec2{ ImGui::GetContentRegionAvail().x, lineHeight });
		if (ImGui::BeginDragDropTarget())
		{
			if (returnType == DragDropTypes::FileSystem)
			{
				if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("FILESYSTEM_TARGET"))
				{
					target = *(Target*)payload->Data;
				}
			}
			else if (returnType == DragDropTypes::Entity)
			{
				if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("ENTITY_TARGET"))
				{
					target = *(Target*)payload->Data;
				}
			}

			ImGui::EndDragDropTarget();
		}
	}
}