#include "mlpch.h"
#include "Scene.h"

#include "Entity.h"
#include "EntityList.h"

#include <Merlin/Core/Components/Camera.h>
#include <Merlin/Core/Components/SpriteRenderer.h>
#include <Merlin/Renderer/Renderer2D.h>

namespace Merlin
{
	std::vector<Entity*> s_Entities;
	std::vector<EntityIndex> s_FreeEntities;
	std::vector<ComponentPool*> s_ComponentPools;

	std::vector<Entity*> s_EntitiesToDelete;
	std::unordered_map<Entity*, int> s_ComponentsToDelete;

	SceneState Scene::s_SceneState;
	WizardStack Scene::s_WizardStack;

	void Scene::OnAwake()
	{
		s_SceneState = SceneState::Edit;
	}

	void Scene::OnDestroy()
	{
		for (auto ent : s_Entities)
			ent->DestroyEntity();

		FlushScene();
	}

	void Scene::OnRuntimeUpdate()
	{
		if (s_SceneState != SceneState::Play) return;

		// Update Native Scripts

		for (Entity* ent : EntityList<NativeScriptComponent>(true))
		{
			for (NativeScriptComponent* nsc : ent->GetComponentsOfBase<NativeScriptComponent>())
			{
				nsc->OnUpdate();
			}
		}

		// Update Wizards

		for (Wizard* wizard : s_WizardStack)
		{
			wizard->OnUpdate();
		}

		// Update Renderer

		Camera* mainCamera = nullptr;
		Transform* cameraTransform = nullptr;

		for (Entity* ent : EntityList<Camera>())
		{
			if (Renderer::CameraRenderer::GetActive() == ent->GetComponent<Camera>()->GetRenderer())
			{
				mainCamera = ent->GetComponent<Camera>();
				cameraTransform = ent->GetTransform();
			}
		}

		if (mainCamera)
		{
			Renderer::Renderer2D::BeginScene(mainCamera->GetRenderer(), cameraTransform->position);

			for (Entity* ent : EntityList<SpriteRenderer>())
			{
				SpriteRenderer* sRend = ent->GetComponent<SpriteRenderer>();

				Renderer::Renderer2D::DrawQuad(ent->GetTransform(), sRend->material, sRend->sprite, sRend->color);
			}

			Renderer::Renderer2D::EndScene();
		}
	}

	void Scene::OnEditorUpdate(Renderer::CameraRenderer* camera, const Vector3& position)
	{
		if (s_SceneState != SceneState::Edit) return;

		Renderer::Renderer2D::BeginScene(camera, position);

		for (Entity* ent : EntityList<SpriteRenderer>())
		{
			SpriteRenderer* sRend = ent->GetComponent<SpriteRenderer>();

			Renderer::Renderer2D::DrawQuad(ent->GetTransform(), sRend->material, sRend->sprite, sRend->color);
		}

		Renderer::Renderer2D::EndScene();
	}

	void Scene::OnFixedUpdate()
	{
		for (Wizard* wizard : s_WizardStack)
		{
			wizard->OnFixedUpdate();
		}
	}

	void Scene::OnEvent(Events::Event& e)
	{
		for (Wizard* wizard : s_WizardStack)
		{
			wizard->OnEvent(e);
		}
	}

	void Scene::SetSceneState(SceneState state)
	{
		s_SceneState = state;
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

	bool Scene::IsEntityValid(EntityID id)
	{
		return (id >> 32) != EntityIndex(-1) && s_Entities[GetEntityIndex(id)]->m_ID == id;
	}

	bool Scene::IsEntityValid(Entity* ent)
	{
		if (ent == nullptr) return false;
		return IsEntityValid(ent->m_ID);
	}

	EntityID Scene::CreateEntityID(EntityIndex index, EntityVersion version)
	{
		return ((EntityID)index << 32) | ((EntityID)version);
	}

	void Scene::PurgeEntity(Entity* ent)
	{
		if (!IsEntityValid(ent)) return;

		EntityIndex index = GetEntityIndex(ent->m_ID);
		EntityID newID = CreateEntityID(EntityIndex(-1), GetEntityVersion(ent->m_ID) + 1);

		s_Entities[index]->m_ID = newID;
		s_Entities[index]->m_Components.reset();
		s_Entities[index]->m_Children.clear();

		if (s_Entities[index]->m_Parent != nullptr)
			s_Entities[index]->m_Parent->RemoveChildEntity(s_Entities[index]);
		s_Entities[index]->m_Parent = nullptr;

		s_FreeEntities.push_back(index);
	}

	void Scene::PurgeComponent(Entity* ent, int component)
	{
		if (!IsEntityValid(ent)) return;

		for (ComponentPool* pool : s_ComponentPools)
		{
			if (pool->ComponentID = component)
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