#include "wvpch.h"
#include "Scene.h"

#include "Entity.h"
#include "EntityList.h"

#include <Wyvern/Core/Components/Camera.h>
#include <Wyvern/Core/Components/Tag.h>
#include <Wyvern/Core/Components/Transform.h>
#include <Wyvern/Core/Components/SpriteRenderer.h>
#include <Wyvern/Renderer/Renderer2D.h>

namespace Wyvern
{
	std::vector<Entity*> s_EntitiesToDelete;
	std::unordered_map<Entity*, int> s_ComponentsToDelete;

	Ref<Scene> Scene::s_ActiveScene;

	Scene::Scene()
		: m_ComponentCounter(0)
	{

	}

	Scene::~Scene()
	{

	}

	void Scene::OnAwake()
	{
		m_SceneState = SceneState::Edit;
	}

	void Scene::OnDestroy()
	{
		for (auto ent : m_Entities)
			ent->DestroyEntity();

		FlushScene();
	}

	void Scene::OnRuntimeUpdate()
	{
		if (m_SceneState != SceneState::Play) return;

		// Update Native Scripts

		for (Entity* ent : EntityList<NativeScriptComponent>(true))
		{
			for (NativeScriptComponent* nsc : GetComponentsOfBase<NativeScriptComponent>(ent))
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

		for (Entity* ent : EntityList<Camera>())
		{
			if (Renderer::CameraRenderer::GetActive() == Scene::GetComponent<Camera>(ent)->GetRenderer())
			{
				mainCamera = Scene::GetComponent<Camera>(ent);
				cameraTransform = ent->GetTransform();
			}
		}

		if (mainCamera)
		{
			Renderer::Renderer2D::BeginScene(mainCamera->GetRenderer(), cameraTransform->GetTransform());

			for (Entity* ent : EntityList<SpriteRenderer>())
			{
				SpriteRenderer* sRend = Scene::GetComponent<SpriteRenderer>(ent);

				Renderer::Renderer2D::DrawQuad(ent->GetTransform(), sRend->material, sRend->sprite, sRend->color);
			}

			Renderer::Renderer2D::EndScene();
		}
	}

	void Scene::OnEditorUpdate(Renderer::CameraRenderer* camera, const Matrix4x4& position)
	{
		if (m_SceneState != SceneState::Edit) return;

		Renderer::Renderer2D::BeginScene(camera, position);

		for (Entity* ent : EntityList<SpriteRenderer>())
		{
			SpriteRenderer* sRend = Scene::GetComponent<SpriteRenderer>(ent);

			Renderer::Renderer2D::DrawQuad(ent->GetTransform(), sRend->material, sRend->sprite, sRend->color);
		}

		Renderer::Renderer2D::EndScene();
	}

	void Scene::OnFixedUpdate()
	{
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
		for (Entity* ent : s_EntitiesToDelete)
			PurgeEntity(ent);

		for (auto& comp : s_ComponentsToDelete)
			PurgeComponent(comp.first, comp.second);

		s_EntitiesToDelete.clear();
		s_ComponentsToDelete.clear();
	}

	void Scene::DestoryEntity(Entity* ent)
	{
		s_EntitiesToDelete.push_back(ent);
		for (Entity* child : ent->m_Children)
			child->DestroyEntity();
	}

	EntityIndex Scene::GetEntityIndex(EntityID id)
	{
		return id >> 32;
	}

	EntityVersion Scene::GetEntityVersion(EntityID id)
	{
		return (EntityVersion)id;
	}

	bool Scene::IsEntityValid(Ref<Scene> scene, EntityID id)
	{
		return (id >> 32) != EntityIndex(-1);
	}

	bool Scene::IsEntityValid(Entity* ent)
	{
		if (ent == nullptr) return false;
		return IsEntityValid(ent->m_Scene, ent->m_ID);
	}

	void Scene::RemoveComponent(Entity* ent, int component)
	{
		s_ComponentsToDelete[ent] = component;
	}

	EntityID Scene::CreateEntityID(EntityIndex index, EntityVersion version)
	{
		return ((EntityID)index << 32) | ((EntityID)version);
	}

	void Scene::CreateEntityDefaults(Ref<Scene> scene, Entity* ent, std::string name)
	{
		ent->m_Scene = scene;
		ent->m_Components.reset();
		ent->m_Transform = AddComponent<Transform>(ent);
		ent->m_Tag = AddComponent<Tag>(ent);
		ent->m_Tag->name = name;
		ent->OnAttach();
	}

	void Scene::PurgeEntity(Entity* ent)
	{
		if (!IsEntityValid(ent)) return;

		Ref<Scene> scene = ent->m_Scene;

		EntityIndex index = GetEntityIndex(ent->m_ID);
		EntityID newID = CreateEntityID(EntityIndex(-1), GetEntityVersion(ent->m_ID) + 1);

		scene->m_Entities[index]->m_ID = newID;
		scene->m_Entities[index]->m_Components.reset();
		scene->m_Entities[index]->m_Children.clear();
		scene->m_Entities[index]->m_ComponentPtrs.clear();

		if (scene->m_Entities[index]->m_Parent != nullptr)
			scene->m_Entities[index]->m_Parent->RemoveChildEntity(scene->m_Entities[index]);
		scene->m_Entities[index]->m_Parent = nullptr;

		scene->m_FreeEntities.push_back(index);
	}

	void Scene::PurgeComponent(Entity* ent, int component)
	{
		if (!IsEntityValid(ent)) return;

		for (ComponentPool* pool : ent->m_Scene->m_ComponentPools)
		{
			if (pool->ComponentID == component)
			{
				for (int i = 0; i < ent->m_ComponentPtrs.size(); i++)
				{
					if (ent->m_ComponentPtrs[i] == pool->Get(GetEntityIndex(ent->m_ID)))
					{
						ent->m_ComponentPtrs.erase(ent->m_ComponentPtrs.begin() + i);
					}
				}
			}
		}

		ent->m_Components.reset(component);
	}
}