#include "wvpch.h"
#include "Entity.h"

#include "Scene.h"

#include <Wyvern/Core/Components/Tag.h>
#include <Wyvern/Core/Components/Transform.h>

namespace Wyvern
{
	Entity::Entity()
	{
		m_EntityRegister = EntityRegister(false);
	}

	Entity::Entity(EntityRegister& view)
	{
		m_EntityRegister = view;
	}
	
	UUID Entity::GetUUID() const
	{
		return m_EntityRegister.UniqueID;
	}

	SceneID Entity::GetSceneID() const
	{
		return m_EntityRegister.SceneID;
	}

	Ref<Scene> Entity::GetScene() const
	{
		return m_EntityRegister.SceneRef;
	}

	Entity Entity::GetParent() const
	{
		return Scene::GetEntity(m_EntityRegister.SceneRef, m_EntityRegister.Parent);
	}

	std::vector<UUID> Entity::GetChildren() const
	{
		return m_EntityRegister.Children;
	}

	Tag* Entity::GetTag()
	{
		return Scene::GetComponent<Tag>(m_EntityRegister);
	}

	Transform* Entity::GetTransform()
	{
		return Scene::GetComponent<Transform>(m_EntityRegister);
	}

	std::vector<Component*> Entity::GetComponents()
	{
		return Scene::GetComponents(Scene::GetEntity(m_EntityRegister.SceneRef, m_EntityRegister.UniqueID));
	}

	void Entity::AddChildEntity(EntityRegister& entity)
	{
		Scene::AddChildEntity(m_EntityRegister, entity);
	}

	void Entity::RemoveChildEntity(EntityRegister& entity)
	{
		Scene::RemoveChildEntity(m_EntityRegister, entity);
	}

	void Entity::DestroyEntity()
	{
		Scene::DestoryEntity(m_EntityRegister);
	}

	bool Entity::IsValid()
	{
		return Scene::IsEntityValid(m_EntityRegister);
	}
}