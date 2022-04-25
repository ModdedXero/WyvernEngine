#pragma once

#include "Entity.h"

#include <Merlin/Core/ApplicationDomain.h>

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

				

#define MCLASS(CLASS)	constexpr int Register { ApplicationDomain::RegisterComponentType<CLASS>(typeid(CLASS).name()); return 0; }
#define MPROPERTY()
#define MFUNCTION()

#define __CLASS__ std::remove_reference<decltype(classMacroImpl(this))>::type
	template <class T> T& classMacroImpl(const T* t);
}