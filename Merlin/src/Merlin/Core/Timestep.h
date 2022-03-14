#pragma once

#include "Constants.h"

namespace Merlin
{
	class Timestep
	{
	public:
		Timestep(float time = 0.0f, float deltaTime = 0.0f)
			: m_Time(time), m_DeltaTime(deltaTime)
		{}

		operator float() const { return m_Time; }

		float GetSeconds() const { return m_Time; }
		float GetMilliseconds() const { return m_Time * 1000; }
		float GetDeltaTime() const { return m_DeltaTime; }
		float GetFPS() const { return 1 / m_DeltaTime; }
		float GetFixedDeltaTime() const { return Constants::FixedUpdateInterval; }
	private:
		float m_Time;
		float m_DeltaTime;
	};
}