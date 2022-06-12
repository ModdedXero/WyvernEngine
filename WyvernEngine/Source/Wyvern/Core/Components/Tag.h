#pragma once

#include <Wyvern/Core/Scene/Component.h>

#include <string>

namespace Wyvern
{
	struct Tag : public Component<Tag, std::string>
	{
		Tag() {}
		~Tag() {}

		std::string name;

		virtual void DrawEditor() override;
	};
}