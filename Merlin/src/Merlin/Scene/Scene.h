#pragma once

#include <Merlin/Scene/ComponentPool.h>
#include <Merlin/Scene/Components.h>
#include <Merlin/Scene/Entity.h>

#include <vector>

namespace Merlin
{
	class Scene
	{
		friend class Entity;
	public:
		static inline Entity CreateEntity()
		{
			if (!s_FreeEntities.empty())
			{
				EntityIndex index = s_FreeEntities.back();
				s_FreeEntities.pop_back();
				EntityID id = CreateEntityID(index, GetEntityVersion(s_Entities[index].m_ID));
				s_Entities[index].m_ID = id;
				s_Entities[index].m_Components.reset();
				return s_Entities[index];
			}

			Entity entity = { CreateEntityID(s_Entities.size(), 0), ComponentMask() };
			s_Entities.push_back(entity);
			s_Entities.back().m_Components.reset();
			// s_Entities.back().AddComponent<Transform>();
			s_Entities.back().DefaultComponents();
			return s_Entities.back();
		}

		static inline void DestroyEntity(EntityID id)
		{
			EntityID newID = CreateEntityID(EntityIndex(-1), GetEntityVersion(id) + 1);
			s_Entities[GetEntityIndex(id)].m_ID = newID;
			s_Entities[GetEntityIndex(id)].m_Components.reset();
			s_FreeEntities.push_back(GetEntityIndex(id));
		}

		template <typename T>
		static inline T* AddComponent(EntityID id)
		{
			if (s_Entities[GetEntityIndex(id)].m_ID != id)
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

			s_Entities[GetEntityIndex(id)].m_Components.set(componentID);

			return component;
		}

		template <typename T>
		static inline T* GetComponent(EntityID id)
		{
			if (s_Entities[GetEntityIndex(id)].GetID() != id)
				return nullptr;

			int componentID = GetComponentID<T>();

			if (!s_Entities[GetEntityIndex(id)].m_Components.test(componentID))
				return nullptr;

			T* component = static_cast<T*>(s_ComponentPools[componentID]->Get(GetEntityIndex(id)));
			return component;
		}

		template <typename T>
		static inline void RemoveComponent(EntityID id)
		{
			if (s_Entities[GetEntityIndex(id)].ID != id)
				return;

			int component = GetComponentID<T>();
			s_Entities[GetEntityIndex(id)].m_Components.reset(component);
		}

		static inline std::vector<Entity> GetEntities()
		{
			return s_Entities;
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

		static EntityIndex GetEntityIndex(EntityID id)
		{
			return id >> 32;
		}
		static EntityVersion GetEntityVersion(EntityID id)
		{
			return (EntityVersion)id;
		}
		static bool IsEntityValid(EntityID id)
		{
			return (id >> 32) != EntityIndex(-1);
		}
	private:
		static inline std::vector<Entity> s_Entities;
		static inline std::vector<ComponentPool*> s_ComponentPools;
		static inline std::vector<EntityIndex> s_FreeEntities;

		static inline int s_ComponentCounter;

		static EntityID CreateEntityID(EntityIndex index, EntityVersion version)
		{
			return ((EntityID)index << 32) | ((EntityID)version);
		}
	};

	// ComponentList from Archetype
	template <typename... ComponentTypes>
	struct ComponentList
	{
		ComponentList()
		{
			if (sizeof...(ComponentTypes) == 0)
			{
				All = true;
			}
			else
			{
				int componentIDs[] = { 0, Scene::GetComponentID<ComponentTypes>()... };
				for (int i = 1; i < (sizeof...(ComponentTypes) + 1); i++)
					Components.set(componentIDs[i]);
			}
		}

		struct Iterator
		{
			Iterator(EntityIndex index, ComponentMask components, bool all)
				: index(index), components(components), all(all)
			{}

			Entity operator*() const
			{
				return Scene::GetEntities()[index];
			}

			bool operator==(const Iterator& other) const
			{
				return index == other.index || index == Scene::GetEntities().size();
			}

			bool operator!=(const Iterator& other) const
			{
				return index != other.index && index != Scene::GetEntities().size();
			}

			Iterator& operator++()
			{
				do
				{
					index++;
				} while (index < Scene::GetEntities().size() && !isValidIndex());
				return *this;
			}

			bool isValidIndex()
			{
				return Scene::IsEntityValid(Scene::GetEntities()[index].GetID()) &&
					(all || components == (components & Scene::GetEntities()[index].GetMask()));
			}

			EntityIndex index;
			ComponentMask components;
			bool all;
		};

		const Iterator begin() const
		{
			int firstIndex = 0;
			while (firstIndex < Scene::GetEntities().size() &&
				(Components != (Components & Scene::GetEntities()[firstIndex].GetMask())
					|| !Scene::IsEntityValid(Scene::GetEntities()[firstIndex].GetID())))
			{
				firstIndex++;
			}

			return Iterator(firstIndex, Components, All);
		}

		const Iterator end() const
		{
			return Iterator(EntityIndex(Scene::GetEntities().size()), Components, All);
		}

		EntityIndex Index = 0;
		ComponentMask Components = 0;
		bool All = false;
	};
}