#pragma once

#include <Merlin.h>

#include <string>

namespace Merlin
{
	class EditorWindow
	{
		friend class EditorLayer;
	public:
		EditorWindow() {}
		virtual ~EditorWindow() {}

		virtual const char* GetWindowTitle() const = 0;
	protected:
		void BeginRender();
		void EndRender();

		virtual void OnGUI() {}

		Vector2 WindowSize;
	};
}