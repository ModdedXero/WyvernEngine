#include "mlpch.h"
#include "Scene.h"

#include "Entity.h"

namespace Merlin
{
	std::vector<Entity*> s_Entities;
	std::vector<EntityIndex> s_FreeEntities;
	std::vector<ComponentPool*> s_ComponentPools;

	std::vector<Entity*> s_EntitiesToDelete;
	std::unordered_map<Entity*, int> s_ComponentsToDelete;

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

	void Scene::FlushScene()
	{
		for (Entity* ent : s_EntitiesToDelete)
			PurgeEntity(ent);

		for (auto& comp : s_ComponentsToDelete)
			PurgeComponent(comp.first, comp.second);

		s_EntitiesToDelete.clear();
		s_ComponentsToDelete.clear();
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
		ent->m_Components.reset(component);
	}
}