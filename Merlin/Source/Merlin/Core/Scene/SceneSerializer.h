#pragma once

#include "Entity.h"
#include <yaml-cpp/yaml.h>

namespace Merlin
{
	class SceneSerializer
	{
	public:
		static void Serialize(const std::string& filepath);
		static void SerializeRuntime(const std::string& filepath);

		static bool Deserialize (const std::string& filepath);
		static bool DeserizlizeRuntime(const std::string& filepath);
	private:
		static void SerializeEntity(YAML::Emitter& out, Entity* ent);
	};
}