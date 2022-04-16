#pragma once

#include <Merlin.h>

#include <Excalibur/Core/EditorWindow.h>
#include <Excalibur/Core/ViewportCamera.h>

namespace Merlin
{
	class Viewport : public EditorWindow
	{
	public:
		Viewport();

		const char* GetWindowTitle() const { return "Viewport"; }

		virtual void OnGUI() override;
	private:
		ViewportCamera* m_Camera;
	};
}