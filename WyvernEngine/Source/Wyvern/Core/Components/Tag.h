#pragma once

#include <Wyvern/Core/Scene/Component.h>

#include <string>

namespace Wyvern
{
	struct Tag : public Component
	{
		Tag() {}
		~Tag() {}

		std::string name;

		WV_SERIALIZE_COMPONENT(Tag)
		WV_SERIALIZE_VARIABLE(std::string, name)
		WV_SERIALIZE_COMPONENT_END
	};
}