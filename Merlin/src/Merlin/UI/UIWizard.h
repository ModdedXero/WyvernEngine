#pragma once

#include <Merlin/Core/Scene/Wizard.h>
#include <Merlin/Events/MouseEvent.h>

namespace Merlin::UI
{
	class UIWizard : public Wizard
	{
	public:
		void OnEvent(Events::Event& event) override;

		bool OnMouseMoveEvent(Events::MouseMovedEvent& e);
		bool OnMouseClickEvent(Events::MouseButtonPressedEvent& e);
	};
}