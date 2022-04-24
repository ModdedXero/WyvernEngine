#pragma once

#include "Constants.h"

namespace Merlin
{
	class Timestep
	{
		friend class Application;
	public:
		static float GetSeconds() { return m_Time; }
		static float GetMilliseconds() { return m_Time * 1000; }
		static float GetDeltaTime() { return m_DeltaTime; }
		static float GetFPS() { return 1 / m_DeltaTime; }
		static float GetFixedDeltaTime() { return Constants::FixedUpdateInterval; }

		operator float() const { return m_Time; }
	protected:
		static inline float m_Time = 0;
		static inline float m_DeltaTime = 0;
	};
}