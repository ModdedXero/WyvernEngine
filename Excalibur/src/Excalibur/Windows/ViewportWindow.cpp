#include "ViewportWindow.h"

#include <imgui.h>

namespace Merlin::Editor
{
	ViewportWindow::ViewportWindow()
	{
		m_Camera = Scene::CreateEntity<ViewportCamera>("Viewport Camera");
	}

	void ViewportWindow::OnGUI()
	{
		if (IsFocused() && IsHovered())
			m_Camera->MoveCamera();

		Vector2 windowPanelSize = GetWindowSize();
		if (WindowSize != windowPanelSize)
		{
			Renderer::Renderer2D::Framebuffer->Resize(windowPanelSize);
			WindowSize = windowPanelSize;

			m_Camera->Resize(windowPanelSize.x, windowPanelSize.y);
		}

		unsigned int textureID = Renderer::Renderer2D::Framebuffer->GetColorAttachmentRendererID();
		ImGui::Image((void*)textureID, ImVec2{ WindowSize.x, WindowSize.y });
	}
}