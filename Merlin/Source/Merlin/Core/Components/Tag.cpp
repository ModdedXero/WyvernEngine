#include "mlpch.h"
#include "Tag.h"

#include <Merlin/Core/Scene/Entity.h>
#include <Merlin/Core/Scene/SerializeHelper.h>

namespace Merlin
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