#pragma once

#include <Wyvern.h>

#include <WyvernEditor.h>
#include <WyvernBuilder/Core/ViewportCamera.h>

using namespace Wyvern::Editor;

namespace Wyvern
{
	class ViewportWindow : public EditorWindow
	{
	public:
		const char* GetWindowTitle() const { return "Viewport"; }

		virtual void OnAttach() override;
		virtual void OnGUI() override;
		virtual void OnEvent(Events::Event& e) override;
		
	private:
		Vector2 m_WindowSize;

		Ref<Renderer::Framebuffer> m_Framebuffer;
		Entity m_HoverEntity;

		int m_GizmoSelection = -1;
		float m_SnapValue = 0.5f;
		bool m_IsSnap = false;

		bool OnKeyPressedEvent(Events::KeyPressedEvent& e);
		bool OnKeyReleasedEvent(Events::KeyReleasedEvent& e);
		bool OnMouseButtonPressed(Events::MouseButtonPressedEvent& e);
		bool OnMouseScrolledEvent(Events::MouseScrolledEvent& e);
	};
}