#pragma once

#include "EntityConstants.h"
#include "ComponentPool.h"

#include "Transform.h"
#include "Tag.h"
#include "Component.h"

#include <Merlin/Core/Debug.h>

#include <vector>
#include <typeinfo>

namespace Merlin
{
	class Entity;

	class Scene
	{
		template <class... ComponentTypes>
		friend struct EntityList;
	public:
		template <typename T>
		static inline T* CreateEntity(std::string name = "Entity", std::string type = "Default")
		{
			if (s_Entities.size() >= MaxEntities)
			{
				DEBUG_LOG_ERROR("Scene: MaxEntity count reached; ", MaxEntities);
				throw std::invalid_argument("Scene: MaxEntity count reached");
				return nullptr;
			}
			if (!std::is_base_of<Entity, T>())
			{
				DEBUG_LOG_ERROR("Scene: Entity or Inherited class required: ", typeid(T).name(), " was provided");
				throw std::invalid_argument("Scene: Type provided was not Entity");
				return nullptr;
			}

			if (!s_FreeEntities.empty())
			{
				EntityIndex index = s_FreeEntities.back();
				s_FreeEntities.pop_back();
				EntityID id = CreateEntityID(index, GetEntityVersion(s_Entities[index]->m_ID));
				SetupEntity(id);
				s_Entities[index]->m_ID = id;
				s_Entities[index]->m_Components.reset();
				s_Entities[index]->m_isDeleting = false;
				Transform* ts = AddComponent<Transform>(s_Entities[index]->m_ID);
				Tag* tag = AddComponent<Tag>(s_Entities[index]->m_ID);
				tag->name = name;
				tag->type = type;
				s_Entities[index]->m_Transform = ts;
				s_Entities[index]->m_Tag = tag;
				s_Entities[index]->OnAttach();
				return (T*)s_Entities[index];
			}

			T* entity = new T();
			entity->m_ID = CreateEntityID((EntityIndex)s_Entities.size(), 0);
			entity->m_Components = ComponentMask();

			s_Entities.push_back(entity);
			s_Entities.back()->m_Components.reset();

			Transform* ts = AddComponent<Transform>(s_Entities.back()->m_ID);
			Tag* tag = AddComponent<Tag>(s_Entities.back()->m_ID);
			tag->name = name;
			tag->type = type;
			s_Entities.back()->m_Transform = ts;
			s_Entities.back()->m_Tag = tag;

			s_Entities.back()->OnAttach();
			return (T*)s_Entities.back();
		}
		static void SetupEntity(EntityID id);

		static void DestoryEntity(EntityID id);
		static void DestoryEntity(Entity* entity);

		static EntityIndex GetEntityIndex(EntityID id);
		static EntityVersion GetEntityVersion(EntityID id);
		static bool IsEntityValid(EntityID id);
		static bool IsEntityValid(Entity* ent);
	public:
		template <typename T>
		static inline T* AddComponent(EntityID id)
		{
			if (s_Entities[GetEntityIndex(id)]->m_ID != id)
				return nullptr;

			if (!std::is_base_of<Component, T>())
			{
				DEBUG_LOG_ERROR("Scene: Component or Inherited class required: ", typeid(T).name(), " was provided");
				throw std::invalid_argument("Scene: Type provided was not Component");
				return nullptr;
			}

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
			component->m_Entity = s_Entities[GetEntityIndex(id)];
			component->m_Transform = s_Entities[GetEntityIndex(id)]->m_Transform;
			component->m_Tag = s_Entities[GetEntityIndex(id)]->m_Tag;

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
		static inline int GetComponentID()
		{
			for (ComponentPool* pool : s_ComponentPools)
				if (pool->ComponentType == typeid(T).name())
					return pool->ComponentID;

			int index = s_ComponentCounter++;
			return index;
		}

		template <typename T>
		static inline int FindComponentID()
		{
			for (ComponentPool* pool : s_ComponentPools)
				if (pool->ComponentType == typeid(T).name())
					return pool->ComponentID;

			return -1;
		}
	public:
		static size_t GetEntityCount() { return s_Entities.size(); }
	private:
		static inline std::vector<Entity*> s_Entities;
		static inline std::vector<EntityIndex> s_FreeEntities;
		static inline std::vector<ComponentPool*> s_ComponentPools;

		static inline int s_ComponentCounter;

		static EntityID CreateEntityID(EntityIndex index, EntityVersion version);
	};
}