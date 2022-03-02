#pragma once

#include <Merlin/Scene/Entity.h>

#include <vector>
#include <string>

namespace Merlin
{
	class Scene
	{
	public:
		static Entity CreateEntity();
		static void DestroyEntity();

		template <typename T>
		static T* AddComponent(EntityID id);
		template <typename T>
		static T* GetComponent(EntityID id);
		template <typename T>
		static void RemoveComponent(EntityID id);
	private:
		static std::vector<Entity> s_Entities;
		static std::vector<const char*, ComponentPool> s_ComponentPools;
	};

	struct ComponentPool
	{

	};
}