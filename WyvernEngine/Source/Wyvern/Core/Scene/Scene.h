#pragma once

#include "EntityConstants.h"
#include "ComponentPool.h"
#include "WizardStack.h"
#include "Entity.h"

#include <Wyvern/Events/Event.h>
#include <Wyvern/Core/Debug.h>
#include <Wyvern/Renderer/CameraRenderer.h>

#include <vector>
#include <typeinfo>
#include <unordered_map>
#include <type_traits>

namespace Wyvern
{
	class Entity;
	struct Transform;
	struct Tag;
	struct Component;

	enum class SceneState
	{
		Play,
		Edit
	};

	class Scene : public std::enable_shared_from_this<Scene>
	{
		template <class... ComponentTypes>
		friend struct EntityList;
		friend class Serializer;
	public:
		Scene();
		~Scene();

		void OnAwake();
		void OnDestroy();
		void OnRuntimeUpdate();
		void OnEditorUpdate(Renderer::CameraRenderer* camera, const Matrix4x4& position);
		void OnFixedUpdate();
		void OnEvent(Events::Event& e);

		template <typename T>
		void CreateWizard();
		template <typename T>
		void DestroyWizard();

		SceneState GetSceneState() { return m_SceneState; }
		void SetSceneState(SceneState state);

		size_t GetEntityCount() { return m_Entities.size(); }

		static void FlushScene();

		static Ref<Scene> GetActiveScene() { return s_ActiveScene; }
		static void SetActiveScene(Ref<Scene> scene) { s_ActiveScene = scene; }

	public:
		static Entity* CreateEntity(Ref<Scene> scene, std::string name = "Entity");
		static Entity* DuplicateEntity(Entity* entity);
		static void DestoryEntity(Entity* entity);

		static EntityIndex GetEntityIndex(EntityID id);
		static EntityVersion GetEntityVersion(EntityID id);
		static bool IsEntityValid(Ref<Scene> scene, EntityID id);
		static bool IsEntityValid(Entity* entity);

	public:
		template <typename T>
		static T* AddComponent(Entity* entity);
		template <typename T>
		static T* AddComponent(Ref<Scene> scene, EntityID entID);
		template <typename T>
		static T* GetComponent(Entity* entity);
		template <typename T>
		static std::vector<T*> GetComponentsOfBase(Entity* entity);
		template <typename T>
		static void RemoveComponent(Entity* entity);
		static void RemoveComponent(Entity* entity, int component);

		template <typename T>
		inline int GetComponentID();
		template <typename T>
		inline int FindComponentID(bool isBase = false);

	private:
		SceneState m_SceneState;

		std::vector<Entity*> m_Entities;
		std::vector<EntityIndex> m_FreeEntities;
		std::vector<ComponentPool*> m_ComponentPools;

		WizardStack m_WizardStack;

		int m_ComponentCounter;

	private:
		static Ref<Scene> s_ActiveScene;

		static inline std::vector<Entity*> s_EntitiesToDelete;
		static inline std::unordered_map<Entity*, int> s_ComponentsToDelete;

		static EntityID CreateEntityID(EntityIndex index, EntityVersion version);
		static void CreateEntityDefaults(Ref<Scene> scene, Entity* entity, std::string name = "Entity");

		static void PurgeEntity(Entity* entity);
		static void PurgeComponent(Entity* entity, int component);
	};

	template <typename T>
	inline T* Scene::AddComponent(Entity* entity)
	{
		return AddComponent<T>(entity->m_Scene, entity->m_ID);
	}

	template<typename T>
	inline T* Scene::AddComponent(Ref<Scene> scene, EntityID entID)
	{
		if (!IsEntityValid(scene, entID)) return nullptr;

		if (!std::is_base_of<Component, T>())
		{
			DEBUG_LOG_ERROR("Scene: Component or Inherited class required: ", typeid(T).name(), " was provided");
			throw std::invalid_argument("Scene: Type provided was not Component");
			return nullptr;
		}

		int componentID = scene->GetComponentID<T>();

		if (scene->m_Entities[GetEntityIndex(entID)]->m_Components.test(componentID))
		{
			DEBUG_CORE_ERROR("Scene: Component ", typeid(T).name(), " already exists on this entity");
			return GetComponent<T>(scene->m_Entities[GetEntityIndex(entID)]);
		}

		if (scene->m_ComponentPools.size() <= componentID)
		{
			scene->m_ComponentPools.resize(componentID + 1, nullptr);
		}

		if (scene->m_ComponentPools[componentID] == nullptr)
		{
			scene->m_ComponentPools[componentID] = new ComponentPool(sizeof(T), typeid(T).name(), typeid(T::base).name(), componentID);
		}

		T* component = new (scene->m_ComponentPools[componentID]->Get(GetEntityIndex(entID))) T();
		component->m_Entity = scene->m_Entities[GetEntityIndex(entID)];
		component->m_Transform = scene->m_Entities[GetEntityIndex(entID)]->m_Transform;
		component->m_Tag = scene->m_Entities[GetEntityIndex(entID)]->m_Tag;
		component->m_ComponentID = componentID;

		scene->m_Entities[GetEntityIndex(entID)]->m_Components.set(componentID);

		// Do not add default components of Tag and Transform to entity component list
		if (!std::is_same<T, Tag>().value && !std::is_same<T, Transform>().value)
			scene->m_Entities[GetEntityIndex(entID)]->m_ComponentPtrs.push_back(component);

		return component;
	}

	template <typename T>
	inline T* Scene::GetComponent(Entity* entity)
	{
		if (!IsEntityValid(entity)) return nullptr;

		int componentID = entity->m_Scene->FindComponentID<T>();

		if (componentID == -1 || !entity->m_Components.test(componentID))
			return nullptr;

		T* component = static_cast<T*>(entity->m_Scene->m_ComponentPools[componentID]->Get(GetEntityIndex(entity->m_ID)));
		return component;
	}

	template<typename T>
	inline std::vector<T*> Scene::GetComponentsOfBase(Entity* entity)
	{
		std::vector<T*> components;

		for (ComponentPool* pool : entity->m_Scene->m_ComponentPools)
		{
			if (pool->ComponentBaseType == typeid(T).name())
				if (entity->m_Components.test(pool->ComponentID))
					components.push_back(static_cast<T*>(pool->Get(GetEntityIndex(entity->m_ID))));
		}

		return components;
	}

	template <typename T>
	inline void Scene::RemoveComponent(Entity* entity)
	{
		s_ComponentsToDelete[entity] = entity->m_Scene->FindComponentID<T>();
	}

	template<typename T>
	inline int Scene::GetComponentID()
	{
		for (ComponentPool* pool : this->m_ComponentPools)
			if (pool->ComponentType == typeid(T).name())
				return pool->ComponentID;

		int index = m_ComponentCounter++;
		return index;
	}

	template <typename T>
	inline int Scene::FindComponentID(bool isBase)
	{
		for (ComponentPool* pool : m_ComponentPools)
			if (isBase ? pool->ComponentBaseType == typeid(T::base).name() : pool->ComponentType == typeid(T).name())
				return pool->ComponentID;

		return -1;
	}

	template<typename T>
	inline void Scene::CreateWizard()
	{
		m_WizardStack.PushWizard(new T());
	}

	template<typename T>
	inline void Scene::DestroyWizard()
	{
		// Add removal of Wizard
	}
}