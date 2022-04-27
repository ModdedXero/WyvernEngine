#pragma once

#include <Wyvern.h>

#include <Excalibur/Core/EditorWindow.h>
#include <Excalibur/Editor/ViewportCamera.h>

namespace Wyvern::Editor
{
	class ViewportWindow : public EditorWindow
	{
	public:
		const char* GetWindowTitle() const { return "Viewport"; }

		virtual void OnGUI() override;
		virtual void OnEvent(Events::Event& e) override;
		
	private:
		int m_GizmoSelection = -1;
		float m_SnapValue = 0.5f;
		bool m_IsSnap = false;

		bool OnKeyPressedEvent(Events::KeyPressedEvent& e);
		bool OnKeyReleasedEvent(Events::KeyReleasedEvent& e);
	};
}