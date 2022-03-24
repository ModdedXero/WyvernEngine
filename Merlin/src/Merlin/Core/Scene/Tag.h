#pragma once

#include "Component.h"

#include <string>

namespace Merlin
{
	struct Tag : public Component
	{
		Tag() {}
		~Tag() {}

		std::string name;
		std::string type;
	};
}