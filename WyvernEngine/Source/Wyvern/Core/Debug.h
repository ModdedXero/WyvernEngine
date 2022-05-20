#pragma once

#include <Wyvern/Core/Math/Vector.h>

#include <string>
#include <iostream>

namespace Wyvern
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

#define DEBUG_LOG(...)							Wyvern::Debug::Log("Application: ", __VA_ARGS__)
#define DEBUG_LOG_WARN(...)						Wyvern::Debug::LogWarn("Application: ", __VA_ARGS__)
#define DEBUG_LOG_ERROR(...)					Wyvern::Debug::LogError("Application: ", __VA_ARGS__)
											
#define DEBUG_CORE(...)							Wyvern::Debug::Log("Wyvern Engine: ", __VA_ARGS__)
#define DEBUG_CORE_WARN(...)					Wyvern::Debug::LogWarn("Wyvern Engine: ", __VA_ARGS__)
#define DEBUG_CORE_ERROR(...)					Wyvern::Debug::LogError("Wyvern Engine: ", __VA_ARGS__)
}