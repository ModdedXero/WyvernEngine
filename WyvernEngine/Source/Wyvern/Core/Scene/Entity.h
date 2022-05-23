#pragma once

#include "EntityRegister.h"

namespace Wyvern
{
	struct Tag;
	struct Transform;
	struct Component;

	class Entity
	{
		friend class Scene;
		friend class Serializer;
		template <typename... ComponentTypes>
		friend class EntityList;

	public:
		Entity();
		Entity(EntityRegister* view);

		UUID GetUUID() const { return m_EntityRegister->UniqueID; }
		SceneID GetSceneID() const { return m_EntityRegister->SceneID; }
		Ref<Scene> GetScene() const { return m_EntityRegister->SceneRef; }
		Entity GetParent() const { return Entity(Scene::GetEntity(GetScene(), m_EntityRegister->Parent)); }
		std::vector<UUID> GetChildren() const { return m_EntityRegister->Children; }

		Tag* GetTag() const;
		Transform* GetTransform() const;
		std::vector<Component*> GetComponents();

		void AddChildEntity(EntityRegister* entity);
		void RemoveChildEntity(EntityRegister* entity);

		void DestroyEntity();

		bool IsValid();

		bool operator ==(const Entity& rhs)
		{
			return m_EntityRegister->UniqueID == rhs.m_EntityRegister->UniqueID;
		}

		operator EntityRegister*()
		{
			return m_EntityRegister;
		}

		operator UUID& ()
		{
			return m_EntityRegister->UniqueID;
		}

	private:
		EntityRegister* m_EntityRegister;
 	};
}