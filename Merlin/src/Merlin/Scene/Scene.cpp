#include "mlpch.h"
#include "Scene.h"

#include <Merlin/Scene/Transform.h>
#include <Merlin/Scene/Tag.h>

namespace Merlin
{
	std::vector<Entity*> s_Entities;
	std::vector<EntityIndex> s_FreeEntities;
	std::vector<ComponentPool*> s_ComponentPools;

	void Scene::DestroyEntity(EntityID id)
	{
		if (!IsEntityValid(id)) return;

		EntityID newID = CreateEntityID(EntityIndex(-1), GetEntityVersion(id) + 1);
		s_Entities[GetEntityIndex(id)]->m_ID = newID;
		s_Entities[GetEntityIndex(id)]->m_Components.reset();
		s_FreeEntities.push_back(GetEntityIndex(id));
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
		return (id >> 32) != EntityIndex(-1);
	}

	EntityID Scene::CreateEntityID(EntityIndex index, EntityVersion version)
	{
		return ((EntityID)index << 32) | ((EntityID)version);
	}
}