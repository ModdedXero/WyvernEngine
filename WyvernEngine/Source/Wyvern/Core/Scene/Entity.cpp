#include "wvpch.h"
#include "Entity.h"

#include "Scene.h"

#include <Wyvern/Core/Components/Tag.h>
#include <Wyvern/Core/Components/Transform.h>

#include <imgui.h>

namespace Wyvern
{
	Entity::Entity()
	{
		m_EntityRegister = nullptr;
	}

	Entity::Entity(EntityRegister* view)
	{
		m_EntityRegister = view;
		if (view) uuid = view->UniqueID;
	}

	Tag* Entity::GetTag() const
	{
		return Scene::GetComponent<Tag>(m_EntityRegister);
	}

	Transform* Entity::GetTransform() const
	{
		return Scene::GetComponent<Transform>(m_EntityRegister);
	}

	std::vector<Component*> Entity::GetComponents()
	{
		return Scene::GetComponents(Scene::GetEntity(m_EntityRegister->SceneRef, m_EntityRegister->UniqueID));
	}

	void Entity::AddChildEntity(EntityRegister* entity)
	{
		Scene::AddChildEntity(m_EntityRegister, entity);
	}

	void Entity::RemoveChildEntity(EntityRegister* entity)
	{
		Scene::RemoveChildEntity(m_EntityRegister, entity);
	}

	void Entity::DestroyEntity()
	{
		Scene::DestoryEntity(m_EntityRegister);
	}

	bool Entity::IsValid()
	{
		if (!m_EntityRegister) return false;
		return Scene::IsEntityValid(m_EntityRegister);
	}
}