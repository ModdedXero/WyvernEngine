#pragma once

#include "Scene.h"
#include "SerializeInfo.h"
#include "SerializeHelper.h"

#include <Wyvern/Tools/FileSystem.h>
#include <Wyvern/Core/Application/ApplicationDomain.h>

#include <memory>
#include <yaml-cpp/yaml.h>

namespace Wyvern
{
	class Entity;

	class Serializer
	{
	public:
		static SerializeInfo& Serialize(Ref<Scene> scene);
		static SerializeInfo& Serialize(EntityRegister* entity);
		static void Serialize(EntityRegister* entity, SerializeInfo& info);
		static void Serialize(SerializeInfo& info, const std::string& filepath);

		static bool Deserialize(Ref<Scene> scene, SerializeInfo& info);
		static bool Deserialize(EntityRegister* entity, SerializeInfo& info);
		static bool Deserialize(Ref<Scene> scene, Tools::FileSystem& filepath);

		static void ConvertSerialToDeserial(SerializeInfo& info);

		static void SerializeRuntime(Ref<Scene> scene, const std::string& filepath);
		static bool DeserizlizeRuntime(Ref<Scene> scene, const std::string& filepath);
	};
}