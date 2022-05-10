#include "EditorWindow.h"

#include <imgui.h>

namespace Wyvern::Editor
{
	void EditorWindow::BeginRender()
	{
		ImGui::Begin(GetWindowTitle());

		// Window Size
		ImVec2 windowPanelSize = ImGui::GetContentRegionAvail();
		m_WindowSize = { windowPanelSize.x, windowPanelSize.y };

		// Window Position
		ImVec2 vMin = ImGui::GetWindowContentRegionMin();
		ImVec2 vMax = ImGui::GetWindowContentRegionMax();
		ImVec2 wPos = ImGui::GetWindowPos();

		vMin.x += wPos.x;
		vMin.y += wPos.y;
		vMax.x += wPos.x;
		vMax.y += wPos.y;

		m_WindowBounds = { vMin.x, vMin.y, vMax.x, vMax.y };

		// Cursor Position
		auto [mx, my] = ImGui::GetMousePos();
		mx -= m_WindowBounds.x;
		my -= m_WindowBounds.y;
		Vector2 viewport = Vector2(m_WindowBounds.x, m_WindowBounds.y) - Vector2(m_WindowBounds.z, m_WindowBounds.w);

		m_CursorPosition = { mx, my };

		// Window States
		m_IsFocused = ImGui::IsWindowFocused();
		m_IsHovered = ImGui::IsWindowHovered();
	}

	void EditorWindow::EndRender()
	{
		ImGui::End();
	}
}