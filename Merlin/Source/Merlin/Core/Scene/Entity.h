#pragma once

#include <Merlin/Core/Base.h>

#include "EntityConstants.h"
#include "Scene.h"

#include <Merlin/Core/Timestep.h>
#include <Merlin/Events/Event.h>
#include <Merlin/Core/Components/Components.h>

#include <bitset>

namespace Merlin
{
	class Scene;
	struct Collision2D;

	class Entity
	{
		friend class Scene;
		friend class EntityWizard;
	protected:
		Entity()
			: m_ID(0), m_Tag(nullptr), m_Transform(nullptr), m_Parent(nullptr), m_EditorOnly(false)
		{}
	public:
		EntityID GetID() { return m_ID; }
		ComponentMask GetMask() { return m_Components; }

		Transform* GetTransform() { return m_Transform; }
		Tag* GetTag() { return m_Tag; }

		bool GetEditorOnly() { return m_EditorOnly; }

		template <typename T>
		inline T* AddComponent() { return Scene::AddComponent<T>(this); }
		template <typename T>
		inline T* GetComponent() { return Scene::GetComponent<T>(this); }
		template <typename T>
		inline std::vector<T*> GetBaseComponents() { return Scene::GetBaseComponents<T>(this); }
		template <typename T>
		inline void RemoveComponent() { Scene::RemoveComponent<T>(this); }

		void DestroyEntity();

		void AddChildEntity(Entity* ent);
		void RemoveChildEntity(Entity* ent);

		std::vector<Entity*> GetChildren() { return m_Children; }

		Entity* GetParent() { return m_Parent; }

		virtual void OnCollision2D(Ref<Collision2D> collision) {}
	protected:
		EntityID m_ID;
		ComponentMask m_Components;
		bool m_EditorOnly;

		Transform* m_Transform;
		Tag* m_Tag;

		Entity* m_Parent;
		std::vector<Entity*> m_Children;

		virtual void OnAttach() {}
 	};
}