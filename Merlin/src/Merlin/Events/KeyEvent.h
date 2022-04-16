#pragma once

#include "Event.h"

#include <sstream>

namespace Merlin::Events
{
	class KeyEvent : public Event
	{
	public:
		inline int GetKeyCode() const { return m_KeyCode; }

	protected:
		KeyEvent(int keycode)
			: m_KeyCode(keycode)
		{}

		int m_KeyCode;
	};

	class KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(int keycode, int repeatCount)
			: KeyEvent(keycode), m_RepeatCount(repeatCount)
		{}

		inline int GetRepeatCount() const { return m_RepeatCount; }
		inline bool IsKeyHeld() const { return m_RepeatCount > 0; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressed Event: " << m_KeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyPressed);
	private:
		int m_RepeatCount;
	};
}