#pragma once

#include "Debug.h"

#include <memory>
#include <filesystem>
#include <initializer_list>

#ifdef WV_DEBUG
	#if defined (WV_PLATFORM_WINDOWS)
		#define WV_DEBUGBREAK() __debugbreak()
	#else
		#error "Platform doesn't support debugbreak yet!"
	#endif
#endif

#ifdef WV_DEBUG
	#define WV_ASSERT(check, ...) { if(!(check)) {DEBUG_LOG_ERROR("Assertion failed at ", std::filesystem::path(__FILE__).filename().string(), ":", __LINE__, " (", __VA_ARGS__, ")"); WV_DEBUGBREAK(); } }
	#define WV_CORE_ASSERT(check, ...) { if(!(check)) {DEBUG_CORE_ERROR("Assertion failed at ", std::filesystem::path(__FILE__).filename().string(), ":", __LINE__, " (", __VA_ARGS__, ")"); WV_DEBUGBREAK(); } }
#else
	#define WV_ASSERT(check, ...) {(check);}
	#define WV_CORE_ASSERT(check, ...) {(check);}
#endif

#define BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

namespace Wyvern
{
	template <typename T>
	using Scope = std::unique_ptr<T>;
	template <typename T, typename ...Args>
	constexpr Scope<T> CreateScope(Args&& ...args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template <typename T>
	using Ref = std::shared_ptr<T>;
	template <typename T, typename ...Args>
	constexpr Ref<T> CreateRef(Args&& ...args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}
}
