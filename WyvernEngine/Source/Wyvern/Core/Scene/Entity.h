#pragma once

#include "EntityConstants.h"

#include <Wyvern/Core/Base.h>
#include <Wyvern/Core/Timestep.h>
#include <Wyvern/Events/Event.h>

#include <bitset>

namespace Wyvern
{
	struct Tag;
	struct Transform;
	struct Component;
	struct Collision2D;

	class Entity
	{
		friend class Scene;
		friend class SceneSerializer;
		friend class EntityWizard;
	protected:
		Entity()
			: m_ID(0), m_Tag(nullptr), m_Transform(nullptr), m_Parent(nullptr)
		{}
	public:
		EntityID GetID() { return m_ID; }
		ComponentMask GetMask() { return m_Components; }

		Transform* GetTransform() { return m_Transform; }
		Tag* GetTag() { return m_Tag; }

		//template <typename T>
		//inline T* AddComponent() { return Scene::AddComponent<T>(this); }

		//template <typename T>
		//inline T* GetComponent() { return Scene::GetComponent<T>(this); }
		//template <typename T>
		//inline std::vector<T*> GetComponentsOfBase() { return Scene::GetComponentsOfBase<T>(this); }

		//template <typename T>
		//inline void RemoveComponent() { Scene::RemoveComponent<T>(this); }
		//inline void RemoveComponent(int component) { Scene::RemoveComponent(this, component); }

		std::vector<Component*> GetAllComponents() { return m_ComponentPtrs; }

		void DestroyEntity();

		void AddChildEntity(Entity* ent);
		void RemoveChildEntity(Entity* ent);

		Entity* GetParent() { return m_Parent; }
		std::vector<Entity*> GetChildren() { return m_Children; }

		virtual void OnCollision2D(Ref<Collision2D> collision) {}
	protected:
		EntityID m_ID;
		ComponentMask m_Components;

		Transform* m_Transform;
		Tag* m_Tag;

		Entity* m_Parent;
		std::vector<Entity*> m_Children;
		std::vector<Component*> m_ComponentPtrs;

		virtual void OnAttach() {}
 	};
}