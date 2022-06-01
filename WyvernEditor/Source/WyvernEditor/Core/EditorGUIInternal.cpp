#include "EditorGUIInternal.h"

#include <Wyvern/Tools/FileSystem.h>
#include <Wyvern/Core/Scene/Entity.h>

#include <imgui.h>
#include <iostream>

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
}