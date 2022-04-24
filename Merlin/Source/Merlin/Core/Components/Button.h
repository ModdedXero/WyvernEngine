#pragma once

#include <Merlin/Core/Scene/Component.h>

namespace Merlin::UI
{
	struct Button : public Component
	{
	private:
		friend class UIWizard;
	public:
		Button() {}
		~Button() {}

		void (*OnClick)() = nullptr;
		void (*OnHoverEnter)() = nullptr;
		void (*OnHoverExit)() = nullptr;
	protected:
		bool m_IsHovering = false;
		bool m_IsClicked = false;
	};
}