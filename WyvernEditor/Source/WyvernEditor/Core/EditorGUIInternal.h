#pragma once

#include "EditorInfo.h"

#include <string>

namespace Wyvern
{
	struct Component;
	class Entity;
}

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
		static void DragDropTarget(DragDropTypes returnType, Target& target);
		static void DragDropSource(DragDropTypes returnType, const void* target, size_t size);

		static void DrawComponent(const std::string label, Component* component, Entity ent, bool isDefault = false);
	};

	template <typename Target>
	inline void EditorGUIInternal::DragDropTarget(DragDropTypes returnType, Target& target)
	{
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