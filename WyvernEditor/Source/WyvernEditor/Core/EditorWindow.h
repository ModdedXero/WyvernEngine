#pragma once

#include <Wyvern/Events/Event.h>
#include <Wyvern/Core/Math/Vector.h>

#include <string>

namespace Wyvern::Editor
{
	class EditorWindow
	{
	public:
		virtual const char* GetWindowTitle() const = 0;

		void BeginRender();
		void EndRender();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnGUI() {}
		virtual void OnEvent(Events::Event& e) {}

		Vector2 GetWindowSize() { return m_WindowSize; }
		Vector4 GetWindowBounds() { return m_WindowBounds; }
		Vector2 GetCursorPosition() { return m_CursorPosition; }

		bool IsFocused() { return m_IsFocused; }
		bool IsHovered() { return m_IsHovered; }

	private:
		Vector2 m_WindowSize;
		Vector4 m_WindowBounds;
		Vector2 m_CursorPosition;

		bool m_IsFocused = false;
		bool m_IsHovered = false;
	};
}