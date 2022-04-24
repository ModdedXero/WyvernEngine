#pragma once

#include <Merlin/Core/Scene/Component.h>

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