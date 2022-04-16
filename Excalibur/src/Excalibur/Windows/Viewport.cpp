#include "Viewport.h"

#include <imgui.h>

namespace Merlin
{
	Viewport::Viewport()
	{
		m_Camera = Scene::CreateEntity<ViewportCamera>();
		Entity* test = Scene::CreateEntity<Entity>();
	}

	void Viewport::OnGUI()
	{
		ImVec2 windowPanelSize = ImGui::GetContentRegionAvail();
		if (WindowSize.x != windowPanelSize.x || WindowSize.y != windowPanelSize.y)
		{
			Renderer::Renderer2D::Framebuffer->Resize({windowPanelSize.x, windowPanelSize.y});
			WindowSize = { windowPanelSize.x, windowPanelSize.y };
		}

		unsigned int textureID = Renderer::Renderer2D::Framebuffer->GetColorAttachmentRendererID();
		ImGui::Image((void*)textureID, ImVec2{ WindowSize.x, WindowSize.y });
	}
}