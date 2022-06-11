#pragma once

#include <yaml-cpp/yaml.h>

namespace Wyvern
{
	struct SerializeInfo
	{
		YAML::Emitter out;
		YAML::Node in;

		SerializeInfo(bool isSerialize)
		{
			m_IsSerialize = isSerialize;
		}

		bool IsSerialize() { return m_IsSerialize; }

	private:
		bool m_IsSerialize;
	};
}