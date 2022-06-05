#pragma once

#include <Wyvern.h>
#include <WyvernEditor.h>

using namespace Wyvern::Editor;

namespace Wyvern
{
	class PropertiesWindow : public EditorWindow
	{
	public:
		const char* GetWindowTitle() const { return "Properties"; }

		virtual void OnGUI() override;

	private:
		WyvernObject* s_SelectedContext;
	};
}