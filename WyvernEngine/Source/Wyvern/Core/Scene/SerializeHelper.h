#pragma once

#include <Wyvern/Core/Math/Math.h>

#include <yaml-cpp/yaml.h>

namespace YAML
{
	template<>
	struct convert<Wyvern::Vector3>
	{
		static YAML::Node encode(const Wyvern::Vector3& rhs)
		{
			YAML::Node node;
			node.push_back(rhs.x);
			node.push_back(rhs.y);
			node.push_back(rhs.z);
			return node;
		}

		static bool decode(const YAML::Node& node, Wyvern::Vector3& rhs)
		{
			if (!node.IsSequence() || node.size() != 3)
				return false;

			rhs.x = node[0].as<float>();
			rhs.y = node[1].as<float>();
			rhs.z = node[2].as<float>();
			return true;
		}
	};

	template<>
	struct convert<Wyvern::Vector4>
	{
		static YAML::Node encode(const Wyvern::Vector4& rhs)
		{
			YAML::Node node;
			node.push_back(rhs.x);
			node.push_back(rhs.y);
			node.push_back(rhs.z);
			node.push_back(rhs.w);
			return node;
		}

		static bool decode(const YAML::Node& node, Wyvern::Vector4& rhs)
		{
			if (!node.IsSequence() || node.size() != 4)
				return false;

			rhs.x = node[0].as<float>();
			rhs.y = node[1].as<float>();
			rhs.z = node[2].as<float>();
			rhs.w = node[3].as<float>();
			return true;
		}
	};
}

namespace Wyvern
{
	YAML::Emitter& operator <<(YAML::Emitter& out, const Vector2& vec);
	YAML::Emitter& operator <<(YAML::Emitter& out, const Vector3& vec);
	YAML::Emitter& operator <<(YAML::Emitter& out, const Vector4& vec);
}