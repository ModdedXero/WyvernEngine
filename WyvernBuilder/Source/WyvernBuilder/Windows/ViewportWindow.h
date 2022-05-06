#pragma once

#include <Wyvern.h>

#include <WyvernEditor.h>
#include <WyvernBuilder/Core/ViewportCamera.h>

namespace Wyvern::Editor
{
	class ViewportWindow : public EditorWindow
	{
	public:
		const char* GetWindowTitle() const { return "Viewport"; }

		virtual void OnAttach() override;
		virtual void OnGUI() override;
		virtual void OnPreRender() override;
		virtual void OnPostRender() override;
		virtual void OnEvent(Events::Event& e) override;
		
	private:
		Renderer::Framebuffer* m_Framebuffer;

		int m_GizmoSelection = -1;
		float m_SnapValue = 0.5f;
		bool m_IsSnap = false;

		bool OnKeyPressedEvent(Events::KeyPressedEvent& e);
		bool OnKeyReleasedEvent(Events::KeyReleasedEvent& e);
	};
}