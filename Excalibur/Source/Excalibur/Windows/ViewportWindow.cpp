#include "ViewportWindow.h"

#include <Excalibur/Core/EditorLayer.h>

#include <imgui.h>

namespace Merlin::Editor
{
	void ViewportWindow::OnGUI()
	{
		if (IsFocused() && IsHovered())
			EditorLayer::GetEditorCamera()->MoveCamera();

		Vector2 windowPanelSize = GetWindowSize();
		if (WindowSize != windowPanelSize)
		{
			Renderer::Renderer2D::Framebuffer->Resize(windowPanelSize);
			WindowSize = windowPanelSize;

			EditorLayer::GetEditorCamera()->Resize(windowPanelSize.x, windowPanelSize.y);
		}

		unsigned int textureID = Renderer::Renderer2D::Framebuffer->GetColorAttachmentRendererID();
		ImGui::Image((void*)textureID, ImVec2{ WindowSize.x, WindowSize.y });
	}
}