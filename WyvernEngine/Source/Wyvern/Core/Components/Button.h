#pragma once

#include <Wyvern/Core/Scene/Component.h>

namespace Wyvern::UI
{
	struct Button : public ComponentBase
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