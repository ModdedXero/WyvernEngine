#include "mlpch.h"
#include "SceneSerializer.h"

#include "Scene.h"

namespace Merlin
{
	void SceneSerializer::Serialize(const std::string& filepath)
	{
		YAML::Emitter out;
		out << YAML::BeginMap;
		out << YAML::Key << "Scene";
		out << YAML::Value << "Scene name here";

		out << YAML::Key << "Entities";
		out << YAML::Value << YAML::BeginSeq;

		for (Entity* ent : Scene::s_Entities)
		{
			if (!Scene::IsEntityValid(ent))
				return;

			SerializeEntity(out, ent);
		}

		out << YAML::EndSeq;
		out << YAML::EndMap;

		std::ofstream fout(filepath);
		fout << out.c_str();
	}

	void SceneSerializer::SerializeRuntime(const std::string& filepath)
	{

	}

	bool SceneSerializer::Deserialize(const std::string& filepath)
	{
		ML_CORE_ASSERT(false, "Not Implemented!");
		return false;
	}

	bool SceneSerializer::DeserizlizeRuntime(const std::string& filepath)
	{
		ML_CORE_ASSERT(false, "Not Implemented!");
		return false;
	}

	void SceneSerializer::SerializeEntity(YAML::Emitter& out, Entity* ent)
	{
		out << YAML::BeginMap;
		out << YAML::Key << "Entity";
		out << YAML::Value << "707034759034570"; // TODO: Add UUID of Entity



		out << YAML::EndMap;
	}
}