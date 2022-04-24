#pragma once

#include <Excalibur/Core/EditorWindow.h>

namespace Merlin::Editor
{
	class PropertiesWindow : public EditorWindow
	{
	public:
		const char* GetWindowTitle() const { return "Properties"; }

		virtual void OnGUI() override;
	private:
		Entity* m_SelectedContext;

		void DrawComponents();
	};
}