#pragma once

#include "Event.h"

#include <sstream>

namespace Merlin::Events
{
	class WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(int width, int height)
			: m_Width(width), m_Height(height)
		{}

		inline int GetWidth() const { return m_Width; }
		inline int GetHeight() const { return m_Height; }

		EVENT_CLASS_TYPE(WindowResize);

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "WindowResize Event: Width [" << m_Width << "] Height [" << m_Height << "]";
			return ss.str();
		}
	protected:
		int m_Width, m_Height;
	};
}