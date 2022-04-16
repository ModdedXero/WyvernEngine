#include "EditorWindow.h"

#include <imgui.h>

namespace Merlin
{
	void EditorWindow::BeginRender()
	{
		ImGui::Begin(GetWindowTitle());
	}

	void EditorWindow::EndRender()
	{
		ImGui::End();
	}
}