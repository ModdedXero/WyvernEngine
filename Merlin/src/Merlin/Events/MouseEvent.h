#pragma once

#include "Event.h"

#include <sstream>

namespace Merlin::Events
{
	class MouseMovedEvent : public Event
	{
	public:
		MouseMovedEvent(int xPos, int yPos)
			: m_xPos(xPos), m_yPos (yPos)
		{}

		inline int GetXPos() const { return m_xPos; }
		inline int GetYPos() const { return m_yPos; }

		EVENT_CLASS_TYPE(MouseMoved);

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseMoved Event: (" << m_xPos << ", " << m_yPos << ")";
			return ss.str();
		}
	private:
		int m_xPos, m_yPos;
	};

	class MouseButtonPressedEvent : public Event
	{
	public:
		MouseButtonPressedEvent(int keycode, int state)
			: m_Keycode(keycode), m_State(state)
		{}

		inline int GetKey() const { return m_Keycode; }
		inline int GetState() const { return m_State; }

		EVENT_CLASS_TYPE(MouseButtonPressed);

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonPressed Event: " << m_Keycode << " Pressed";
			return ss.str();
		}
	private:
		int m_Keycode, m_State;
	};
}