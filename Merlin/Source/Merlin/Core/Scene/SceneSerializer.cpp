#include "mlpch.h"
#include "SceneSerializer.h"

#include "Scene.h"

namespace Merlin
{
	void SceneSerializer::Serialize(const std::string& filepath)
	{
		YAML::Emitter out;
		out << YAML::BeginMap;
		out << YAML::Key << "Scene" << YAML::Value << "Scene name here";
		out << YAML::Key << "Entities" << YAML::Value << YAML::BeginSeq;

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
		std::ifstream stream(filepath);
		std::stringstream strStream;
		strStream << stream.rdbuf();

		YAML::Node data = YAML::Load(strStream.str());
		if (!data["Scene"])
			return false;

		std::string sceneName = data["Scene"].as<std::string>();
		DEBUG_CORE("Deserilizing scene ", sceneName);

		auto entities = data["Entities"];
		if (entities)
		{
			for (auto ent : entities)
			{
				Entity* entity = Scene::CreateEntity<Entity>();
				auto components = ent["Components"];
				if (components)
				{
					for (auto comp : components)
					{
						auto compBase = ApplicationDomain::CreateComponent(comp.first.as<std::string>());
						DEBUG_CORE(comp.first.as<std::string>());
						compBase->Deserialize(entity, comp);
					}
				}
			}
		}
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

		out << YAML::Key << "Components" << YAML::Value << YAML::BeginMap;
		for (Component* comp : ent->m_ComponentPtrs)
			comp->Serialize(out);
		out << YAML::EndMap;

		out << YAML::EndMap;
	}
}