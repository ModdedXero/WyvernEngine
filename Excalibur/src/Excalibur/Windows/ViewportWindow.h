#pragma once

#include <Merlin.h>

#include <Excalibur/Core/EditorWindow.h>
#include <Excalibur/Editor/ViewportCamera.h>

namespace Merlin::Editor
{
	class ViewportWindow : public EditorWindow
	{
	public:
		ViewportWindow();

		const char* GetWindowTitle() const { return "Viewport"; }

		virtual void OnGUI() override;
	private:
		ViewportCamera* m_Camera;
	};
}