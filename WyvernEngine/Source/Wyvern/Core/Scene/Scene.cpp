#include "wvpch.h"
#include "Scene.h"

#include "Entity.h"
#include "EntityList.h"

#include <Wyvern/Core/Components/Camera.h>
#include <Wyvern/Core/Components/Tag.h>
#include <Wyvern/Core/Components/Transform.h>
#include <Wyvern/Core/Components/SpriteRenderer.h>
#include <Wyvern/Renderer/Renderer2D.h>
#include <Wyvern/Core/Physics/Physics2DWizard.h>

namespace Wyvern
{
	std::vector<Entity*> s_EntitiesToDelete;
	std::unordered_map<Entity*, int> s_ComponentsToDelete;

	Ref<Scene> Scene::s_ActiveScene;

	Scene::Scene()
		: m_ComponentCounter(0)
	{
		CreateWizard<Physics2DWizard>();
	}

	Scene::~Scene()
	{

	}

	void Scene::OnAttach()
	{
		if (m_SceneState == SceneState::Play)
		{
			for (Entity* entity : EntityList<NativeScriptComponent>(shared_from_this(), true))
			{
				for (NativeScriptComponent* nsc : GetComponentsOfBase<NativeScriptComponent>(entity))
				{
					nsc->OnAttach();
				}
			}
		}
	}

	void Scene::OnDestroy()
	{
		for (auto& entity : m_Entities)
			entity->DestroyEntity();

		for (auto& pool : m_ComponentPools)
			delete pool;

		FlushScene();
	}

	void Scene::OnRuntimeUpdate()
	{
		if (m_SceneState != SceneState::Play) return;

		// Update Native Scripts

		for (Entity* entity : EntityList<NativeScriptComponent>(shared_from_this(), true))
		{
			for (NativeScriptComponent* nsc : GetComponentsOfBase<NativeScriptComponent>(entity))
			{
				nsc->OnUpdate();
			}
		}

		// Update Wizards

		for (Wizard* wizard : m_WizardStack)
		{
			wizard->OnUpdate();
		}

		// Update Renderer

		Camera* mainCamera = nullptr;
		Transform* cameraTransform = nullptr;
		Entity* mainCameraCache = nullptr;

		for (Entity* entity : EntityList<Camera>(shared_from_this()))
		{
			if (!mainCameraCache) mainCameraCache = entity;

			if (Scene::GetComponent<Camera>(entity)->IsActive())
			{
				mainCamera = Scene::GetComponent<Camera>(entity);
				cameraTransform = entity->GetTransform();
				break;
			}
		}

		if (!mainCamera && mainCameraCache)
		{
			mainCamera = Scene::GetComponent<Camera>(mainCameraCache);
			cameraTransform = mainCameraCache->GetTransform();
			mainCamera->SetActive();
		}

		if (mainCamera)
		{
			Renderer::Renderer2D::BeginScene(mainCamera->GetRenderer(), cameraTransform);

			for (Entity* entity : EntityList<SpriteRenderer>(shared_from_this()))
			{
				SpriteRenderer* sRend = Scene::GetComponent<SpriteRenderer>(entity);

				Renderer::Renderer2D::DrawQuad(entity->GetTransform(), sRend->material, sRend->sprite, sRend->color, GetSceneIndex(entity->m_SceneID));
			}

			Renderer::Renderer2D::EndScene();
		}
	}

	void Scene::OnEditorUpdate(Renderer::CameraRenderer* camera, Transform* position)
	{
		if (m_SceneState != SceneState::Edit) return;

		Renderer::Renderer2D::BeginScene(camera, position);

		for (Entity* entity : EntityList<SpriteRenderer>(shared_from_this()))
		{
			SpriteRenderer* sRend = Scene::GetComponent<SpriteRenderer>(entity);

			Renderer::Renderer2D::DrawQuad(entity->GetTransform(), sRend->material, sRend->sprite, sRend->color, GetSceneIndex(entity->m_SceneID));
		}

		Renderer::Renderer2D::EndScene();
	}

	void Scene::OnFixedUpdate()
	{
		if (m_SceneState != SceneState::Play) return;

		for (Entity* entity : EntityList<NativeScriptComponent>(shared_from_this(), true))
		{
			for (NativeScriptComponent* nsc : GetComponentsOfBase<NativeScriptComponent>(entity))
			{
				nsc->OnFixedUpdate();
			}
		}

		for (Wizard* wizard : m_WizardStack)
		{
			wizard->OnFixedUpdate();
		}
	}

	void Scene::OnEvent(Events::Event& e)
	{
		for (Wizard* wizard : m_WizardStack)
		{
			wizard->OnEvent(e);
		}
	}

	void Scene::SetSceneState(SceneState state)
	{
		m_SceneState = state;
	}

	void Scene::FlushScene()
	{
		for (Entity* entity : s_EntitiesToDelete)
			PurgeEntity(entity);

		for (auto& comp : s_ComponentsToDelete)
			PurgeComponent(comp.first, comp.second);

		s_EntitiesToDelete.clear();
		s_ComponentsToDelete.clear();
	}

	void Scene::SetActiveScene(Ref<Scene> scene)
	{
		s_ActiveScene = scene;
#ifndef WV_DEBUG
		s_ActiveScene->m_SceneState = SceneState::Play;
#endif
	}

	Entity* Scene::CreateEntity(Ref<Scene> scene, std::string name)
	{
		if (scene->m_Entities.size() >= MaxEntities)
		{
			DEBUG_LOG_ERROR("Scene: MaxEntity count reached; ", MaxEntities);
			throw std::invalid_argument("Scene: MaxEntity count reached");
			return nullptr;
		}

		if (!scene->m_FreeEntities.empty())
		{
			SceneIndex index = scene->m_FreeEntities.back();
			scene->m_FreeEntities.pop_back();
			SceneID id = CreateSceneID(index, GetSceneVersion(scene->m_Entities[index]->m_SceneID));
			scene->m_Entities[index]->m_SceneID = id;
			CreateEntityDefaults(scene, scene->m_Entities[index], name);

			return scene->m_Entities[index];
		}

		Entity* entity = new Entity();
		entity->m_SceneID = CreateSceneID((SceneIndex)scene->m_Entities.size(), 0);
		entity->m_Components = ComponentMask();
		scene->m_Entities.push_back(entity);

		CreateEntityDefaults(scene, scene->m_Entities.back(), name);

		return scene->m_Entities.back();
	}

	Entity* Scene::CreateEntity(Ref<Scene> scene, const UUID& uuid)
	{
		Entity* ent = FindEntity(scene, uuid);

		if (!ent)
		{
			ent = CreateEntity(scene, "Entity");
			ent->m_UUID = uuid;
		}

		return ent;
	}

	Entity* Scene::FindEntity(Ref<Scene> scene, const UUID& uuid)
	{
		for (Entity* entity : scene->m_Entities)
		{
			if (entity->m_UUID == uuid)
				return entity;
		}

		return nullptr;
	}

	Entity* Scene::GetEntityAtIndex(Ref<Scene> scene, int index)
	{
		if (index >= 0 && index < scene->m_Entities.size() && IsEntityValid(scene->m_Entities[index]))
			return scene->m_Entities[index];

		return nullptr;
	}

	Entity* Scene::DuplicateEntity(Entity* entity, Entity* parent)
	{
		Entity* newEnt = CreateEntity(entity->m_Scene, entity->m_Tag->name);

		SerializeInfo& entData = Serializer::Serialize(entity);
		Serializer::ConvertSerialToDeserial(entData);

		if (parent)
		{
			if (entData.in["Parent"])
				entData.in["Parent"] = (uint64_t)parent->m_UUID;
		}

		Serializer::Deserialize(newEnt, entData);

		for (Entity* child : entity->m_Children)
		{
			DuplicateEntity(child, newEnt);
		}

		return newEnt;
	}

	void Scene::DestoryEntity(Entity* entity)
	{
		s_EntitiesToDelete.push_back(entity);
		for (Entity* child : entity->m_Children)
			child->DestroyEntity();
	}

	SceneIndex Scene::GetSceneIndex(SceneID id)
	{
		return id >> 32;
	}

	SceneVersion Scene::GetSceneVersion(SceneID id)
	{
		return (SceneVersion)id;
	}

	bool Scene::IsEntityValid(Ref<Scene> scene, SceneID id)
	{
		return (id >> 32) != SceneIndex(-1);
	}

	bool Scene::IsEntityValid(Entity* entity)
	{
		if (entity == nullptr) return false;
		return IsEntityValid(entity->m_Scene, entity->m_SceneID);
	}

	void Scene::RemoveComponent(Entity* entity, int component)
	{
		s_ComponentsToDelete[entity] = component;
	}

	SceneID Scene::CreateSceneID(SceneIndex index, SceneVersion version)
	{
		return ((SceneID)index << 32) | ((SceneID)version);
	}

	void Scene::CreateEntityDefaults(Ref<Scene> scene, Entity* entity, std::string name)
	{
		entity->m_Scene = scene;
		entity->m_Components.reset();
		entity->m_Transform = AddComponent<Transform>(entity);
		entity->m_Tag = AddComponent<Tag>(entity);
		entity->m_Tag->name = name;
		entity->m_UUID = UUID();
	}

	void Scene::PurgeEntity(Entity* entity)
	{
		if (!IsEntityValid(entity)) return;

		Ref<Scene> scene = entity->m_Scene;

		SceneIndex index = GetSceneIndex(entity->m_SceneID);
		SceneID newID = CreateSceneID(SceneIndex(-1), GetSceneVersion(entity->m_SceneID) + 1);

		scene->m_Entities[index]->m_SceneID = newID;
		scene->m_Entities[index]->m_Components.reset();
		scene->m_Entities[index]->m_Children.clear();
		scene->m_Entities[index]->m_ComponentPtrs.clear();
		scene->m_Entities[index]->m_Scene = nullptr;

		if (scene->m_Entities[index]->m_Parent != nullptr)
			scene->m_Entities[index]->m_Parent->RemoveChildEntity(scene->m_Entities[index]);
		scene->m_Entities[index]->m_Parent = nullptr;

		scene->m_FreeEntities.push_back(index);
	}

	void Scene::PurgeComponent(Entity* entity, int component)
	{
		if (!IsEntityValid(entity)) return;

		for (auto& pool : entity->m_Scene->m_ComponentPools)
		{
			if (pool->ComponentID == component)
			{
				for (int i = 0; i < entity->m_ComponentPtrs.size(); i++)
				{
					if (entity->m_ComponentPtrs[i] == pool->Get(GetSceneIndex(entity->m_SceneID)))
					{
						entity->m_ComponentPtrs.erase(entity->m_ComponentPtrs.begin() + i);
					}
				}
			}
		}

		entity->m_Components.reset(component);
	}
}