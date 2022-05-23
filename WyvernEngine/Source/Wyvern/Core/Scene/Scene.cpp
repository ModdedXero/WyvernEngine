#include "wvpch.h"
#include "Scene.h"

#include "EntityList.h"
#include "EntityRegister.h"

#include <Wyvern/Core/Components/Camera.h>
#include <Wyvern/Core/Components/Tag.h>
#include <Wyvern/Core/Components/Transform.h>
#include <Wyvern/Core/Components/SpriteRenderer.h>
#include <Wyvern/Renderer/Renderer2D.h>
#include <Wyvern/Core/Physics/Physics2DWizard.h>

namespace Wyvern
{
	std::vector<EntityRegister*> s_EntitiesToDelete;
	std::unordered_map<EntityRegister*, int> s_ComponentsToDelete;

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
			for (EntityRegister* entity : EntityList<NativeScriptComponent>(shared_from_this(), true))
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
		for (EntityRegister* entity : m_Entities)
			DestoryEntity(entity);

		for (ComponentPool* pool : m_ComponentPools)
			delete pool;

		FlushScene();
	}

	void Scene::OnRuntimeUpdate()
	{
		if (m_SceneState != SceneState::Play) return;

		// Update Native Scripts

		for (EntityRegister* entity : EntityList<NativeScriptComponent>(shared_from_this(), true))
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

		Camera* mainCamera = Camera::GetActiveCamera();

		if (mainCamera)
		{
			Renderer::Renderer2D::BeginScene(mainCamera->GetRenderer(), mainCamera->GetTransform(), mainCamera->clearColor);

			for (EntityRegister* entity : EntityList<SpriteRenderer>(shared_from_this()))
			{
				SpriteRenderer* sRend = Scene::GetComponent<SpriteRenderer>(entity);

				Renderer::Renderer2D::DrawQuad(GetComponent<Transform>(entity), sRend->material, sRend->sprite, sRend->color, GetSceneIndex(entity->SceneID));
			}

			Renderer::Renderer2D::EndScene();
		}
	}

	void Scene::OnEditorUpdate(Renderer::CameraRenderer* camera, Transform* position)
	{
		if (m_SceneState != SceneState::Edit) return;

		if (Camera::GetActiveCamera())
			Renderer::Renderer2D::BeginScene(camera, position, Camera::GetActiveCamera()->clearColor);
		else
			Renderer::Renderer2D::BeginScene(camera, position);

		for (EntityRegister* entity : EntityList<SpriteRenderer>(shared_from_this()))
		{
			SpriteRenderer* sRend = Scene::GetComponent<SpriteRenderer>(entity);

			Renderer::Renderer2D::DrawQuad(GetComponent<Transform>(entity), sRend->material, sRend->sprite, sRend->color, GetSceneIndex(entity->SceneID));
		}

		Renderer::Renderer2D::EndScene();
	}

	void Scene::OnFixedUpdate()
	{
		if (m_SceneState != SceneState::Play) return;

		for (EntityRegister* entity : EntityList<NativeScriptComponent>(shared_from_this(), true))
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
		for (EntityRegister* entity : s_EntitiesToDelete)
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

	EntityRegister* Scene::CreateEntity(Ref<Scene> scene, std::string name)
	{
		if (scene->m_Entities.size() >= MaxEntities)
		{
			DEBUG_LOG_ERROR("Scene: MaxEntity count reached; ", MaxEntities);
			throw std::invalid_argument("Scene: MaxEntity count reached");
			return new EntityRegister(false);
		}

		if (!scene->m_FreeEntities.empty())
		{
			SceneIndex index = scene->m_FreeEntities.back();
			scene->m_FreeEntities.pop_back();
			SceneID id = CreateSceneID(index, GetSceneVersion(scene->m_Entities[index]->SceneID));
			scene->m_Entities[index]->SceneID = id;
			CreateEntityDefaults(scene, scene->m_Entities[index], name);

			return scene->m_Entities[index];
		}

		EntityRegister* entity = new EntityRegister();
		entity->SceneID = CreateSceneID((SceneIndex)scene->m_Entities.size(), 0);
		entity->Components = ComponentMask();
		scene->m_Entities.push_back(entity);

		CreateEntityDefaults(scene, scene->m_Entities.back(), name);

		return scene->m_Entities.back();
	}

	EntityRegister* Scene::CreateEntity(Ref<Scene> scene, const UUID& uuid)
	{
		if ((uint64_t)uuid == 0) return new EntityRegister(false);

		EntityRegister* ent = GetEntity(scene, uuid);

		if (!IsEntityValid(ent))
		{
			ent = CreateEntity(scene, "Entity");
			ent->UniqueID = uuid;
		}

		return ent;
	}

	EntityRegister* Scene::GetEntity(Ref<Scene> scene, const UUID& uuid)
	{
		if ((uint64_t)uuid == 0 || !scene) return new EntityRegister(false);

		for (EntityRegister* entity : scene->m_Entities)
		{
			if (entity->UniqueID == uuid)
				return entity;
		}

		return new EntityRegister(false);
	}

	EntityRegister* Scene::GetEntity(Ref<Scene> scene, int index)
	{
		if (index >= 0 && index < scene->m_Entities.size() && IsEntityValid(scene->m_Entities[index]))
			return scene->m_Entities[index];

		return new EntityRegister(false);
	}

	EntityRegister* Scene::DuplicateEntity(EntityRegister* entity, EntityRegister* parent)
	{
		EntityRegister* newEnt = CreateEntity(entity->SceneRef, GetComponent<Tag>(entity)->name);

		SerializeInfo& entData = Serializer::Serialize(entity);
		Serializer::ConvertSerialToDeserial(entData);

		if (IsEntityValid(parent))
		{
			if (entData.in["Parent"])
				entData.in["Parent"] = (uint64_t)parent->UniqueID;
		}

		Serializer::Deserialize(newEnt, entData);

		for (UUID& child : entity->Children)
		{
			DuplicateEntity(GetEntity(entity->SceneRef, child), newEnt);
		}

		return newEnt;
	}

	void Scene::DestoryEntity(EntityRegister* entity)
	{
		s_EntitiesToDelete.push_back(entity);
		for (UUID& child : entity->Children)
			DestoryEntity(GetEntity(entity->SceneRef, child));
	}

	void Scene::AddChildEntity(EntityRegister* parent, EntityRegister* child)
	{
		for (UUID& id : parent->Children)
			if (id == child->UniqueID)
				return;

		child->Parent = parent->UniqueID;
		parent->Children.push_back(child->UniqueID);
	}

	void Scene::RemoveChildEntity(EntityRegister* parent, EntityRegister* child)
	{
		for (int i = 0; i < parent->Children.size(); i++)
		{
			if (parent->Children[i] == child->UniqueID)
			{
				parent->Children.erase(parent->Children.begin() + i);
				return;
			}
		}
	}

	SceneIndex Scene::GetSceneIndex(SceneID id)
	{
		return id >> 32;
	}

	SceneVersion Scene::GetSceneVersion(SceneID id)
	{
		return (SceneVersion)id;
	}

	bool Scene::IsEntityValid(SceneID id)
	{
		return (id >> 32) != SceneIndex(-1);
	}

	bool Scene::IsEntityValid(EntityRegister* entity)
	{
		if (!entity->SceneRef ||
			(SceneVersion)entity->SceneRef->m_Entities[GetSceneIndex(entity->SceneID)]->SceneID != (SceneVersion)entity->SceneID)
			return false;

		return entity->UniqueID != 0 && IsEntityValid(entity->SceneID);
	}

	bool Scene::IsEntityValid(Ref<Scene> scene, UUID uuid)
	{
		return uuid != 0 && IsEntityValid(GetEntity(scene, uuid));
	}

	void Scene::RemoveComponent(EntityRegister* entity, int component)
	{
		s_ComponentsToDelete[entity] = component;
	}

	SceneID Scene::CreateSceneID(SceneIndex index, SceneVersion version)
	{
		return (static_cast<unsigned long long>((SceneIndex)index) << 32) | ((SceneID)version);
	}

	std::vector<Component*> Scene::GetComponents(EntityRegister* entity)
	{
		std::vector<Component*> components;

		for (ComponentPool* pool : entity->SceneRef->m_ComponentPools)
			if (entity->Components.test(pool->ComponentID))
				components.push_back(static_cast<Component*>(entity->SceneRef->m_ComponentPools[pool->ComponentID]->Get(GetSceneIndex(entity->SceneID))));

		return components;
	}

	void Scene::CreateEntityDefaults(Ref<Scene> scene, EntityRegister* entity, std::string name)
	{
		entity->SceneRef = scene;
		entity->Components.reset();
		AddComponent<Transform>(entity);
		if (Tag* tag = AddComponent<Tag>(entity))
			tag->name = name;
		entity->UniqueID = UUID();
	}

	void Scene::PurgeEntity(EntityRegister* entity)
	{
		if (!IsEntityValid(entity)) return;

		Ref<Scene> scene = entity->SceneRef;

		SceneIndex index = GetSceneIndex(entity->SceneID);
		SceneID newID = CreateSceneID(SceneIndex(-1), GetSceneVersion(entity->SceneID) + 1);

		scene->m_Entities[index]->SceneID = newID;
		scene->m_Entities[index]->Components.reset();
		scene->m_Entities[index]->Children.clear();
		scene->m_Entities[index]->SceneRef = nullptr;

		EntityRegister* parent = GetEntity(scene, scene->m_Entities[index]->Parent);
		if (IsEntityValid(parent))
			scene->RemoveChildEntity(parent, scene->m_Entities[index]);
		scene->m_Entities[index]->Parent = UUID(0);

		scene->m_FreeEntities.push_back(index);
	}

	void Scene::PurgeComponent(EntityRegister* entity, int component)
	{
		if (!IsEntityValid(entity)) return;

		entity->Components.reset(component);
	}
}