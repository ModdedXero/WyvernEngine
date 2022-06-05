#include "PropertiesWindow.h"

#include <WyvernBuilder/Core/BuilderLayer.h>

#include <imgui.h>
#include <imgui_internal.h>

namespace Wyvern
{
	void PropertiesWindow::OnGUI()
	{
		if (!BuilderLayer::GetSelectedContext()) return;

		s_SelectedContext = BuilderLayer::GetSelectedContext();

		s_SelectedContext->_DrawProperties();
	}
}