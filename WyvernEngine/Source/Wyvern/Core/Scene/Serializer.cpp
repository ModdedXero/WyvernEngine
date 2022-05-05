#include "wvpch.h"
#include "Serializer.h"

#include "Scene.h"
#include "Entity.h"
#include "Component.h"

#include <Wyvern/Core/Components/Tag.h>
#include <Wyvern/Core/Components/Transform.h>

namespace Wyvern
{
	SerializeInfo& Serializer::Serialize(Ref<Scene> scene)
	{
		SerializeInfo* info = new SerializeInfo(true);
		info->out << YAML::BeginMap;
		info->out << YAML::Key << "Scene" << YAML::Value << "Scene name here";
		info->out << YAML::Key << "Entities" << YAML::Value << YAML::BeginSeq;

		for (Entity* entity : scene->m_Entities)
		{
			if (!Scene::IsEntityValid(entity))
				continue;

			Serialize(entity, *info);
		}

		info->out << YAML::EndSeq;
		info->out << YAML::EndMap;

		return *info;
	}

	SerializeInfo& Serializer::Serialize(Entity* entity)
	{
		SerializeInfo* info = new SerializeInfo(true);

		Serialize(entity, *info);

		return *info;
	}

	void Serializer::Serialize(Entity* entity, SerializeInfo& info)
	{
		info.out << YAML::BeginMap;
		info.out << YAML::Key << "Entity" << YAML::Value << entity->m_UUID;
		if (entity->m_Parent) info.out << YAML::Key << "Parent" << YAML::Value << entity->m_Parent->m_UUID;

		info.out << YAML::Key << "Components" << YAML::Value << YAML::BeginMap;

		entity->GetTag()->__Serialize(info);
		entity->GetTransform()->__Serialize(info);
		for (Component* comp : entity->m_ComponentPtrs)
			comp->__Serialize(info);

		info.out << YAML::EndMap;

		info.out << YAML::EndMap;
	}

	void Serializer::Serialize(SerializeInfo& info, const std::string& filepath)
	{
		std::ofstream fout(filepath);
		fout << info.out.c_str();
	}

	bool Serializer::Deserialize(Ref<Scene> scene, SerializeInfo& info)
	{
		std::string sceneName = info.in["Scene"].as<std::string>();
		DEBUG_CORE("Deserilizing scene ", sceneName);

		auto entities = info.in["Entities"];
		if (entities)
		{
			for (auto ent : entities)
			{
				SerializeInfo* entInfo = new SerializeInfo(false);
				entInfo->in = (YAML::Node)ent;
				UUID entUUID = entInfo->in["Entity"].as<UUID>();

				Entity* entity = Scene::CreateEntity(scene, entUUID);

				if (entInfo->in["Parent"])
				{
					UUID parentUUID = entInfo->in["Parent"].as<UUID>();
					Entity* parent = Scene::CreateEntity(scene, parentUUID);
					parent->AddChildEntity(entity);
				}

				Deserialize(entity, *entInfo);
			}
		}

		return true;
	}

	bool Serializer::Deserialize(Entity* entity, SerializeInfo& info)
	{
		DEBUG_CORE(info.in);

		if (info.in["Parent"])
		{
			if (!entity->m_Parent)
			{
				entity->m_Parent = Scene::CreateEntity(entity->m_Scene, info.in["Parent"].as<UUID>());
				entity->m_Parent->AddChildEntity(entity);
			}
		}

		auto components = info.in["Components"];
		if (components)
		{
			for (auto comp : components)
			{
				SerializeInfo compInfo(false);
				compInfo.in = comp.second;
				auto compBase = ApplicationDomain::CreateComponent(comp.first.as<std::string>(), entity->m_Scene, entity->GetSceneID());
				if (compBase) compBase->__Serialize(compInfo);
			}
		}

		return true;
	}

	bool Serializer::Deserialize(Ref<Scene> scene, const std::string& filepath)
	{
		std::ifstream stream(filepath);
		std::stringstream strStream;
		strStream << stream.rdbuf();

		SerializeInfo info(false);
		info.in = YAML::Load(strStream.str());
		if (!info.in["Scene"])
			return false;

		return Deserialize(scene, info);
	}

	void Serializer::ConvertSerialToDeserial(SerializeInfo& info)
	{
		info.in = YAML::Load(info.out.c_str());
	}

	void Serializer::SerializeRuntime(Ref<Scene> scene, const std::string& filepath)
	{
		ML_CORE_ASSERT(false, "Not Implemented!");
	}

	bool Serializer::DeserizlizeRuntime(Ref<Scene> scene, const std::string& filepath)
	{
		ML_CORE_ASSERT(false, "Not Implemented!");
		return false;
	}
}