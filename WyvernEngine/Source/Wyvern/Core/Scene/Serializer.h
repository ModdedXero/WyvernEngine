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

	class Serializer
	{
	public:
		static SerializeInfo& Serialize(Ref<Scene> scene);
		static SerializeInfo& Serialize(Entity* entity);
		static void Serialize(Entity* entity, SerializeInfo& info);
		static void Serialize(SerializeInfo& info, const std::string& filepath);

		static bool Deserialize(Ref<Scene> scene, SerializeInfo& info);
		static bool Deserialize(Entity* entity, SerializeInfo& info);
		static bool Deserialize(Ref<Scene> scene, const std::string& filepath);

		static void ConvertSerialToDeserial(SerializeInfo& info);

		static void SerializeRuntime(Ref<Scene> scene, const std::string& filepath);
		static bool DeserizlizeRuntime(Ref<Scene> scene, const std::string& filepath);
	};

#define WV_SERIALIZE_COMPONENT(CLASS_NAME)			static inline Component* __RegisterComponent(Ref<Scene> scene, unsigned long long entity) { return Scene::AddComponent<CLASS_NAME>(scene, entity); }\
													static inline bool __IsRegistered = ApplicationDomain::RegisterComponent(#CLASS_NAME, __RegisterComponent);\
													virtual void DrawEditor() override;\
													virtual void __Serialize(SerializeInfo& info) override\
													{\
														info.out << YAML::Key << #CLASS_NAME;\
														info.out << YAML::BeginMap;

#define WV_SERIALIZE_VARIABLE(VAR_TYPE, VAR_NAME)		if (info.IsSerialize()) info.out << YAML::Key << #VAR_NAME << YAML::Value << VAR_NAME;\
														else\
														{if (info.in[#VAR_NAME]) VAR_NAME = info.in[#VAR_NAME].as<VAR_TYPE>();}

#define WV_SERIALIZE_COMPONENT_END						info.out << YAML::EndMap;\
													}
}