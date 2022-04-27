#pragma once

#include "Entity.h"

#include <Wyvern/Core/ApplicationDomain.h>

#include <memory>
#include <yaml-cpp/yaml.h>

namespace Wyvern
{
	class SceneSerializer
	{
	public:
		static void Serialize(const std::string& filepath);
		static void SerializeRuntime(const std::string& filepath);

		static bool Deserialize(const std::string& filepath);
		static bool DeserizlizeRuntime(const std::string& filepath);
	private:
		static void SerializeEntity(YAML::Emitter& out, Entity* ent);
	};

#define MCLASS(CLASS)	static std::shared_ptr<Component> RegisterComponent() { return std::make_shared<CLASS>(); }\
						static inline bool IsRegistered = ApplicationDomain::RegisterComponent(#CLASS, RegisterComponent)
#define MPROPERTY()
#define MFUNCTION()
}