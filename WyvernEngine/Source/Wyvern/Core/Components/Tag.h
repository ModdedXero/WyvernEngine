#pragma once

#include <Wyvern/Core/Scene/NativeScriptComponent.h>

#include <string>

namespace Wyvern
{
	struct Tag : public NativeScriptComponent<Tag, std::string>
	{
		Tag() {}
		~Tag() {}

		std::string name;

		virtual void DrawEditor() override;
	};
}