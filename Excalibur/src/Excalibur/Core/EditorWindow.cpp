#include "EditorWindow.h"

#include <imgui.h>

namespace Merlin::Editor
{
	void EditorWindow::BeginRender()
	{
		ImGui::Begin(GetWindowTitle());
	}

	void EditorWindow::EndRender()
	{
		ImGui::End();
	}

	Vector2 EditorWindow::GetWindowSize()
	{
		ImVec2 windowPanelSize = ImGui::GetContentRegionAvail();
		return { windowPanelSize.x, windowPanelSize.y };
	}

	bool EditorWindow::IsFocused()
	{
		return ImGui::IsWindowFocused();
	}

	bool EditorWindow::IsHovered()
	{
		return ImGui::IsWindowHovered();
	}
}