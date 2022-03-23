#pragma once

#include <Merlin/Core/Math/Vector.h>

#include <glad.h>

#include <string>
#include <iostream>

namespace Merlin
{
	class Debug
	{
		struct expandType
		{
			template <typename T>
			expandType(T&&...) {}
		};
	public:
		template <typename... Args>
		static void Log(Args... args)
		{
			expandType{ 0, (std::cout << args, 0)... };
			std::cout << std::endl;
		}

		template <typename... Args>
		static void LogWarn(Args... args)
		{
			expandType{ 0, (std::cout << args, 0)... };
			std::cout << std::endl;
		}

		template <typename... Args>
		static void LogError(Args... args)
		{
			expandType{ 0, (std::cout << args, 0)... };
			std::cout << std::endl;
		}

		static void DrawLine(const Vector2& start, const Vector2& end, float width)
		{

		}
	};

#define DEBUG_LOG(...)							Debug::Log(__VA_ARGS__)
#define DEBUG_LOG_WARN(...)						Debug::LogWarn(__VA_ARGS__)
#define DEBUG_LOG_ERROR(...)					Debug::LogError(__VA_ARGS__)

#define DEBUG_DRAW_LINE(start, end, width)		Debug::DrawLine(start, end, width)
}