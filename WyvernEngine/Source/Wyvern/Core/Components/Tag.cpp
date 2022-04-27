#include "wvpch.h"
#include "Tag.h"

#include <Wyvern/Core/Scene/Entity.h>
#include <Wyvern/Core/Scene/SerializeHelper.h>

namespace Wyvern
{
	void Tag::Serialize(YAML::Emitter& out)
	{
		out << YAML::Key << "Tag";
		out << YAML::BeginMap;

		out << YAML::Key << "name" << YAML::Value << name;

		out << YAML::EndMap;
	}

	void Tag::Deserialize(Entity* ent, YAML::Node& data)
	{
		ent->GetTag()->name = data["name"].as<std::string>();
	}
}