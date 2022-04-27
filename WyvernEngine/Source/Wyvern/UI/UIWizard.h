#pragma once

#include <Wyvern/Core/Scene/Wizard.h>
#include <Wyvern/Events/MouseEvent.h>

namespace Wyvern::UI
{
	class UIWizard : public Wizard
	{
	public:
		void OnEvent(Events::Event& event) override;

		bool OnMouseMoveEvent(Events::MouseMovedEvent& e);
		bool OnMouseClickEvent(Events::MouseButtonPressedEvent& e);
	};
}