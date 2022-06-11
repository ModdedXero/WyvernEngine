#pragma once

#include <xhash>
#include <yaml-cpp/yaml.h>

namespace Wyvern
{
	class UUID
	{
	public:
		UUID();
		UUID(uint64_t uuid);
		UUID(const UUID&) = default;

		operator uint64_t() const { return m_UUID; }

		bool operator ==(const UUID& other) const
		{
			return m_UUID == other.m_UUID;
		}
	private:
		uint64_t m_UUID;
	};

	inline void operator >>(YAML::Node& node, UUID& rhs)
	{
		rhs = node.as<uint64_t>();
	}
}

namespace std
{
	template<>
	struct hash<Wyvern::UUID>
	{
		std::size_t operator ()(const Wyvern::UUID& uuid) const
		{
			return hash<uint64_t>()((uint64_t)uuid);
		}
	};
}