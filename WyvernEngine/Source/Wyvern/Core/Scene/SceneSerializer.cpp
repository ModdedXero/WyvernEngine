#include "wvpch.h"
#include "SceneSerializer.h"

#include "Scene.h"
#include "Entity.h"
#include "Component.h"

#include <Wyvern/Core/Components/Tag.h>
#include <Wyvern/Core/Components/Transform.h>

namespace Wyvern
{
	void SceneSerializer::Serialize(const std::string& filepath)
	{
		SerializeInfo info(true);
		info.out << YAML::BeginMap;
		info.out << YAML::Key << "Scene" << YAML::Value << "Scene name here";
		info.out << YAML::Key << "Entities" << YAML::Value << YAML::BeginSeq;

		for (Entity* ent : Scene::s_Entities)
		{
			if (!Scene::IsEntityValid(ent))
				continue;

			SerializeEntity(info, ent);
		}

		info.out << YAML::EndSeq;
		info.out << YAML::EndMap;

		std::ofstream fout(filepath);
		fout << info.out.c_str();
	}

	void SceneSerializer::SerializeRuntime(const std::string& filepath)
	{

	}

	bool SceneSerializer::Deserialize(const std::string& filepath)
	{
		std::ifstream stream(filepath);
		std::stringstream strStream;
		strStream << stream.rdbuf();

		SerializeInfo info(false);
		info.in = YAML::Load(strStream.str());
		if (!info.in["Scene"])
			return false;

		std::string sceneName = info.in["Scene"].as<std::string>();
		DEBUG_CORE("Deserilizing scene ", sceneName);

		auto entities = info.in["Entities"];
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
						SerializeInfo compInfo(false);
						compInfo.in = comp.second;
						auto compBase = ApplicationDomain::CreateComponent(comp.first.as<std::string>(), entity->GetID());
						compBase->__Serialize(compInfo);
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

	void SceneSerializer::SerializeEntity(SerializeInfo& info, Entity* ent)
	{
		info.out << YAML::BeginMap;
		info.out << YAML::Key << "Entity";
		info.out << YAML::Value << "707034759034570"; // TODO: Add UUID of Entity

		info.out << YAML::Key << "Components" << YAML::Value << YAML::BeginMap;

		ent->GetTag()->__Serialize(info);
		ent->GetTransform()->__Serialize(info);
		for (Component* comp : ent->m_ComponentPtrs)
			comp->__Serialize(info);

		info.out << YAML::EndMap;

		info.out << YAML::EndMap;
	}
}