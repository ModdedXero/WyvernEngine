#pragma once

#include <Merlin.h>

#include <string>

namespace Merlin::Editor
{
	class EditorWindow
	{
		friend class EditorLayer;
	public:
		virtual const char* GetWindowTitle() const = 0;

	protected:
		void BeginRender();
		void EndRender();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnGUI() {}
		virtual void OnEvent(Events::Event& e) {}

		Vector2 GetWindowSize();
		bool IsFocused();
		bool IsHovered();

		Vector2 WindowSize;
	private:
		bool m_IsFocused = false;
		bool m_IsHovered = false;
	};
}