#include "mlpch.h"
#include "Scene.h"

#include <Merlin/Scene/Transform.h>
#include <Merlin/Scene/Tag.h>

namespace Merlin
{
	std::vector<Entity*> s_Entities;
	std::vector<EntityIndex> s_FreeEntities;
	std::vector<ComponentPool*> s_ComponentPools;

	//template <typename T>
	//inline Entity* Scene::CreateEntity()
	//{
	//	if (s_Entities.size() >= MaxEntities)
	//	{
	//		ML_LOG_ERROR("Scene: MaxEntity count reached; ", MaxEntities);
	//		throw std::invalid_argument("Scene: MaxEntity count reached");
	//		return nullptr;
	//	}

	//	if (!s_FreeEntities.empty())
	//	{
	//		EntityIndex index = s_FreeEntities.back();
	//		s_FreeEntities.pop_back();
	//		EntityID id = CreateEntityID(index, GetEntityVersion(s_Entities[index]->m_ID));
	//		s_Entities[index]->m_ID = id;
	//		s_Entities[index]->m_Components.reset();
	//		Transform* ts = AddComponent<Transform>(s_Entities[index]->m_ID);
	//		Tag* tag = AddComponent<Tag>(s_Entities[index]->m_ID);
	//		s_Entities[index]->m_Transform = ts;
	//		s_Entities[index]->m_Tag = tag;
	//		s_Entities[index]->InitDefaultComponents();
	//		return s_Entities[index];
	//	}

	//	Entity* entity = new Entity(CreateEntityID(s_Entities.size(), 0), ComponentMask());
	//	s_Entities.push_back(entity);
	//	s_Entities.back()->m_Components.reset();
	//	Transform* ts = AddComponent<Transform>(s_Entities.back()->m_ID);
	//	Tag* tag = AddComponent<Tag>(s_Entities.back()->m_ID);
	//	s_Entities.back()->m_Transform = ts;
	//	s_Entities.back()->m_Tag = tag;
	//	s_Entities.back()->InitDefaultComponents();
	//	ML_LOG_INFO("Tes");
	//	return s_Entities.back();
	//}

	void Scene::DestroyEntity(EntityID id)
	{
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