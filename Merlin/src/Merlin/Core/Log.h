#pragma once

#include <string>
#include <iostream>

namespace Merlin
{
	class Log
	{
		struct expandType
		{
			template <typename T>
			expandType(T&&...) {}
		};
	public:
		template <typename... Args>
		static void Info(Args... args)
		{
			expandType{ 0, (std::cout << args, 0)... };
			std::cout << std::endl;
		}

		template <typename... Args>
		static void Warn(Args... args)
		{
			expandType{ 0, (std::cout << args, 0)... };
			std::cout << std::endl;
		}

		template <typename... Args>
		static void Error(Args... args)
		{
			expandType{ 0, (std::cout << args, 0)... };
			std::cout << std::endl;
		}
	};

#define ML_LOG_INFO(...)	Log::Info(__VA_ARGS__)
#define ML_LOG_WARN(...)	Log::Warn(__VA_ARGS__)
#define ML_LOG_ERROR(...)	Log::Error(__VA_ARGS__)
}