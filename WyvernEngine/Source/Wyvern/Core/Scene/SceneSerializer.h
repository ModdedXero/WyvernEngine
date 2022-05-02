#pragma once

#include "Scene.h"
#include "SerializeHelper.h"

#include <Wyvern/Core/ApplicationDomain.h>

#include <memory>
#include <yaml-cpp/yaml.h>

namespace Wyvern
{
	class Entity;

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

	class SceneSerializer
	{
	public:
		static void Serialize(const std::string& filepath);
		static void SerializeRuntime(const std::string& filepath);

		static bool Deserialize(const std::string& filepath);
		static bool DeserizlizeRuntime(const std::string& filepath);
	private:
		static void SerializeEntity(SerializeInfo& info, Entity* ent);
	};

#define WV_SERIALIZE_COMPONENT(CLASS_NAME)			static inline Component* __RegisterComponent(unsigned long long ent) { return Scene::AddComponent<CLASS_NAME>(ent); }\
													static inline bool __IsRegistered = ApplicationDomain::RegisterComponent(#CLASS_NAME, __RegisterComponent);\
													virtual void DrawEditor() override;\
													virtual void __Serialize(SerializeInfo& info) override\
													{\
														info.out << YAML::Key << #CLASS_NAME;\
														info.out << YAML::BeginMap;

#define WV_SERIALIZE_VARIABLE(VAR_TYPE, VAR_NAME)		if (info.IsSerialize()) info.out << YAML::Key << #VAR_NAME << YAML::Value << VAR_NAME;\
														else VAR_NAME = info.in[#VAR_NAME].as<VAR_TYPE>();

#define WV_SERIALIZE_COMPONENT_END						info.out << YAML::EndMap;\
													}
}