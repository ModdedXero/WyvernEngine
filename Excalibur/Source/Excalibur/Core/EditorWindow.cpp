#include "EditorWindow.h"

#include <imgui.h>

namespace Merlin::Editor
{
	void EditorWindow::BeginRender()
	{
		ImGui::Begin(GetWindowTitle());
		m_IsFocused = ImGui::IsWindowFocused();
		m_IsHovered = ImGui::IsWindowHovered();
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
		return m_IsFocused;
	}

	bool EditorWindow::IsHovered()
	{
		return m_IsHovered;
	}
}