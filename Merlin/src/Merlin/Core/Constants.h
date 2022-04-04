#pragma once

#include <utility>

namespace Merlin
{
	class Constants
	{
	public:
		static const float FixedUpdateInterval;
	};

#define BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }
}