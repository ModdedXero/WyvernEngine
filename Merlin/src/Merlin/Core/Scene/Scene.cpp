#include "mlpch.h"
#include "Scene.h"

#include "Entity.h"

namespace Merlin
{
	std::vector<Entity*> s_Entities;
	std::vector<EntityIndex> s_FreeEntities;
	std::vector<ComponentPool*> s_ComponentPools;

	void Scene::SetupEntity(EntityID id)
	{
		EntityIndex index = GetEntityIndex(id);
		EntityID newID = CreateEntityID(EntityIndex(-1), GetEntityVersion(id) + 1);
		s_Entities[index]->m_ID = newID;
	}

	void Scene::DestoryEntity(EntityID id)
	{
		EntityIndex index = GetEntityIndex(id);
		if (!IsEntityValid(id)) return;

		s_Entities[index]->m_Components.reset();
		s_Entities[index]->m_isDeleting = true;

		for (Entity* child : s_Entities[index]->m_Children)
			child->DestroyEntity();
		s_Entities[index]->m_Children.clear();
		if (s_Entities[index]->m_Parent != nullptr)
			s_Entities[index]->m_Parent->RemoveChildEntity(s_Entities[index]);
		s_Entities[index]->m_Parent = nullptr;
		s_FreeEntities.push_back(index);
	}

	void Scene::DestoryEntity(Entity* entity)
	{
		DestoryEntity(entity->m_ID);
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
		return (id >> 32) != EntityIndex(-1) && !s_Entities[GetEntityIndex(id)]->m_isDeleting;
	}

	bool Scene::IsEntityValid(Entity* ent)
	{
		if (ent == nullptr) return false;
		return IsEntityValid(ent->GetID());
	}

	EntityID Scene::CreateEntityID(EntityIndex index, EntityVersion version)
	{
		return ((EntityID)index << 32) | ((EntityID)version);
	}
}