#pragma once

#include "EntityRegister.h"

#include <Wyvern/Core/Object.h>

namespace Wyvern
{
	struct Tag;
	struct Transform;
	struct ComponentBase;

	class Entity : public Object
	{
		friend class Scene;
		friend class Serializer;
		template <typename... ComponentTypes>
		friend class EntityList;

	public:
		Entity();
		Entity(EntityRegister* view);

		virtual void _DrawProperties() override;

		UUID GetUUID() const { return m_EntityRegister->UniqueID; }
		SceneID GetSceneID() const { return m_EntityRegister->SceneID; }
		Ref<Scene> GetScene() const { return m_EntityRegister->SceneRef; }
		UUID& GetParent() const { return m_EntityRegister->Parent; }
		std::vector<UUID> GetChildren() const { return m_EntityRegister->Children; }

		Tag* GetTag() const;
		Transform* GetTransform() const;
		std::vector<ComponentBase*> GetComponents();

		template <typename T>
		T* AddComponent() { return Scene::AddComponent<T>(m_EntityRegister); }

	public:
		void AddChildEntity(EntityRegister* entity);
		void RemoveChildEntity(EntityRegister* entity);

		void DestroyEntity();

		bool IsValid() const;
		bool IsActive() const { return m_EntityRegister && m_EntityRegister->IsActive; }
		void SetActive(bool active) { if (m_EntityRegister) m_EntityRegister->IsActive = active; }

	public:
		bool operator ==(const Entity& rhs)
		{
			if (!m_EntityRegister || !rhs.m_EntityRegister) return false;
			return m_EntityRegister->UniqueID == rhs.m_EntityRegister->UniqueID;
		}

		operator bool() const
		{
			return IsValid();
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