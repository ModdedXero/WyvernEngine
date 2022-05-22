#pragma once

#include "UUID.h"
#include "WizardStack.h"
#include "ComponentPool.h"
#include "EntityConstants.h"

#include <Wyvern/Core/Debug.h>
#include <Wyvern/Core/Base.h>
#include <Wyvern/Events/Event.h>
#include <Wyvern/Utils/FileSystem.h>
#include <Wyvern/Renderer/CameraRenderer.h>

#include <bitset>
#include <vector>
#include <typeinfo>
#include <type_traits>
#include <unordered_map>

namespace Wyvern
{
	struct Transform;
	struct Tag;
	struct Component;
	struct EntityRegister;

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
		friend class Project;
	public:
		Scene();
		~Scene();

		void OnAttach();
		void OnDestroy();
		void OnRuntimeUpdate();
		void OnEditorUpdate(Renderer::CameraRenderer* camera, Transform* position);
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
		static void SetActiveScene(Ref<Scene> scene);

	public:
		static EntityRegister& CreateEntity(Ref<Scene> scene, std::string name = "Entity");
		static EntityRegister& CreateEntity(Ref<Scene> scene, const UUID& uuid);
		static EntityRegister& GetEntity(Ref<Scene> scene, const UUID& uuid);
		static EntityRegister& GetEntity(Ref<Scene> scene, int index);
		static EntityRegister& DuplicateEntity(EntityRegister& entity, EntityRegister& parent);
		static void DestoryEntity(EntityRegister& entity);

		static void AddChildEntity(EntityRegister& parent, EntityRegister& child);
		static void RemoveChildEntity(EntityRegister& parent, EntityRegister& child);

		static SceneIndex GetSceneIndex(SceneID id);
		static SceneVersion GetSceneVersion(SceneID id);
		static bool IsEntityValid(SceneID id);
		static bool IsEntityValid(EntityRegister& entity);
		static bool IsEntityValid(Ref<Scene> scene, UUID uuid);

	public:
		template <typename T>
		static T* AddComponent(EntityRegister& entity);
		template <typename T>
		static T* AddComponent(Ref<Scene> scene, SceneID entID);
		template <typename T>
		static T* GetComponent(EntityRegister& entity);
		static std::vector<Component*> GetComponents(EntityRegister& entity);
		template <typename T>
		static std::vector<T*> GetComponentsOfBase(EntityRegister& entity);
		template <typename T>
		static void RemoveComponent(EntityRegister& entity);
		static void RemoveComponent(EntityRegister& entity, int component);

		template <typename T>
		inline int GetComponentID();
		template <typename T>
		inline int FindComponentID();
		template <typename T>
		inline std::vector<int> FindComponentIDs();

		static SceneID CreateSceneID(SceneIndex index, SceneVersion version);
	private:
		Utils::FileSystem m_ScenePath;
		SceneState m_SceneState = SceneState::Edit;

		std::vector<EntityRegister*> m_Entities;
		std::vector<SceneIndex> m_FreeEntities;
		std::vector<ComponentPool*> m_ComponentPools;

		WizardStack m_WizardStack;

		int m_ComponentCounter;

	private:
		static Ref<Scene> s_ActiveScene;

		static inline std::vector<EntityRegister*> s_EntitiesToDelete;
		static inline std::unordered_map<EntityRegister*, int> s_ComponentsToDelete;

		static void CreateEntityDefaults(Ref<Scene> scene, EntityRegister& entity, std::string name = "Entity");

		static void PurgeEntity(EntityRegister& entity);
		static void PurgeComponent(EntityRegister& entity, int component);
	};

	template <typename T>
	inline T* Scene::AddComponent(EntityRegister& entity)
	{
		return AddComponent<T>(entity.SceneRef, entity.SceneID);
	}

	template<typename T>
	inline T* Scene::AddComponent(Ref<Scene> scene, SceneID entID)
	{
		if (!IsEntityValid(entID)) return nullptr;

		if (!std::is_base_of<Component, T>())
		{
			DEBUG_LOG_ERROR("Scene: Component or Inherited class required: ", typeid(T).name(), " was provided");
			throw std::invalid_argument("Scene: Type provided was not Component");
			return nullptr;
		}

		int componentID = scene->GetComponentID<T>();

		if (scene->m_Entities[GetSceneIndex(entID)]->Components.test(componentID))
		{
			return GetComponent<T>(GetEntity(scene, GetSceneIndex(entID)));
		}

		if (scene->m_ComponentPools.size() <= componentID)
		{
			scene->m_ComponentPools.resize(componentID + 1, nullptr);
		}

		if (scene->m_ComponentPools[componentID] == nullptr)
		{
			scene->m_ComponentPools[componentID] = new ComponentPool(sizeof(T), typeid(T).name(), typeid(T::base).name(), componentID);
		}

		T* component = new (scene->m_ComponentPools[componentID]->Get(GetSceneIndex(entID))) T();
		component->m_Entity = *scene->m_Entities[GetSceneIndex(entID)];
		component->m_ComponentID = componentID;

		scene->m_Entities[GetSceneIndex(entID)]->Components.set(componentID);

		return component;
	}

	template <typename T>
	inline T* Scene::GetComponent(EntityRegister& entity)
	{
		if (!IsEntityValid(entity)) return nullptr;

		int componentID = entity.SceneRef->FindComponentID<T>();

		if (componentID == -1 || !entity.Components.test(componentID))
			return nullptr;

		T* component = static_cast<T*>(entity.SceneRef->m_ComponentPools[componentID]->Get(GetSceneIndex(entity.SceneID)));
		return component;
	}

	template<typename T>
	inline std::vector<T*> Scene::GetComponentsOfBase(EntityRegister& entity)
	{
		std::vector<T*> components;

		for (auto& pool : entity.SceneRef->m_ComponentPools)
		{
			if (pool->ComponentBaseType == typeid(T::base).name())
				if (entity.Components.test(pool->ComponentID))
					components.push_back(static_cast<T*>(pool->Get(GetSceneIndex(entity.SceneID))));
		}

		return components;
	}

	template <typename T>
	inline void Scene::RemoveComponent(EntityRegister& entity)
	{
		s_ComponentsToDelete[entity] = entity.Scene->FindComponentID<T>();
	}

	template<typename T>
	inline int Scene::GetComponentID()
	{
		for (auto& pool : this->m_ComponentPools)
			if (pool->ComponentType == typeid(T).name())
				return pool->ComponentID;

		int index = m_ComponentCounter++;
		return index;
	}

	template <typename T>
	inline int Scene::FindComponentID()
	{
		for (auto& pool : m_ComponentPools)
			if (pool->ComponentType == typeid(T).name())
				return pool->ComponentID;

		return -1;
	}

	template <typename T>
	inline std::vector<int> Scene::FindComponentIDs()
	{
		std::vector<int> ids;
		for (auto& pool : m_ComponentPools)
			if (pool->ComponentBaseType == typeid(T::base).name())
				ids.push_back(pool->ComponentID);

		return ids;
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