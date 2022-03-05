#pragma once

#include <Merlin/Scene/ComponentPool.h>
#include <Merlin/Scene/Entity.h>

#include <vector>
#include <typeinfo>

namespace Merlin
{
	class Scene
	{
		friend class Entity;

		template <class... ComponentTypes>
		friend struct ComponentList;
	public:
		static Entity* CreateEntity();
		static void DestroyEntity(EntityID id);

		static EntityIndex GetEntityIndex(EntityID id);
		static EntityVersion GetEntityVersion(EntityID id);
		static bool IsEntityValid(EntityID id);
	public:
		template <typename T>
		static inline T* AddComponent(EntityID id)
		{
			if (s_Entities[GetEntityIndex(id)]->m_ID != id)
				return nullptr;

			int componentID = GetComponentID<T>();

			if (s_ComponentPools.size() <= componentID)
			{
				s_ComponentPools.resize(componentID + 1, nullptr);
			}

			if (s_ComponentPools[componentID] == nullptr)
			{
				s_ComponentPools[componentID] = new ComponentPool(sizeof(T), typeid(T).name(), componentID);
			}

			T* component = new (s_ComponentPools[componentID]->Get(GetEntityIndex(id))) T();

			s_Entities[GetEntityIndex(id)]->m_Components.set(componentID);

			return component;
		}

		template <typename T>
		static inline T* GetComponent(EntityID id)
		{
			if (s_Entities[GetEntityIndex(id)]->GetID() != id)
				return nullptr;

			int componentID = GetComponentID<T>();

			if (!s_Entities[GetEntityIndex(id)]->m_Components.test(componentID))
				return nullptr;

			T* component = static_cast<T*>(s_ComponentPools[componentID]->Get(GetEntityIndex(id)));
			return component;
		}

		template <typename T>
		static inline void RemoveComponent(EntityID id)
		{
			if (s_Entities[GetEntityIndex(id)]->m_ID != id)
				return;

			int component = GetComponentID<T>();
			s_Entities[GetEntityIndex(id)]->m_Components.reset(component);
		}

		template <typename T>
		static int GetComponentID()
		{
			for (ComponentPool* pool : s_ComponentPools)
				if (pool->ComponentType == typeid(T).name())
					return pool->ComponentID;

			int index = s_ComponentCounter++;
			return index;
		}
	private:
		static inline std::vector<Entity*> s_Entities;
		static inline std::vector<EntityIndex> s_FreeEntities;
		static inline std::vector<ComponentPool*> s_ComponentPools;

		static inline int s_ComponentCounter;

		static EntityID CreateEntityID(EntityIndex index, EntityVersion version);
	};
}