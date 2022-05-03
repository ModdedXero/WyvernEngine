#pragma once

#include <WyvernEditor/Core/EditorWindow.h>

namespace Wyvern::Editor
{
	class PropertiesWindow : public EditorWindow
	{
	public:
		const char* GetWindowTitle() const { return "Properties"; }

		virtual void OnGUI() override;
	private:
		Entity* s_SelectedContext;

		void DrawComponents();
	};
}