#include "EditorGUIInternal.h"

#include <imgui.h>
#include <iostream>

namespace Wyvern::Editor
{
	Utils::FileSystem* EditorGUIInternal::DragDropTarget(const char* label, const char* id)
	{
		Utils::FileSystem* target = nullptr;
		ImGui::Button(label);
		if (ImGui::BeginDragDropTarget())
		{
			if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload(id))
			{
				target = (Utils::FileSystem*)payload->Data;
			}

			ImGui::EndDragDropTarget();
		}

		return target ? target : nullptr;
	}
}