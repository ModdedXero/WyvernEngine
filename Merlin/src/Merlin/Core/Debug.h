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
	};

#define DEBUG_LOG(...)							Debug::Log("Application: ", __VA_ARGS__)
#define DEBUG_LOG_WARN(...)						Debug::LogWarn("Application: ", __VA_ARGS__)
#define DEBUG_LOG_ERROR(...)					Debug::LogError("Application: ", __VA_ARGS__)

#define DEBUG_CORE(...)							Debug::Log("Merlin: ", __VA_ARGS__)
#define DEBUG_CORE_WARN(...)					Debug::LogWarn("Merlin: ", __VA_ARGS__)
#define DEBUG_CORE_ERROR(...)					Debug::LogError("Melrin: ", __VA_ARGS__)
}