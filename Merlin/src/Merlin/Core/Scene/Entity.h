#pragma once

#include "EntityConstants.h"

#include "Tag.h"
#include "Transform.h"
#include "Scene.h"

#include <Merlin/Core/Timestep.h>
#include <Merlin/Events/Event.h>

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
			: m_ID(0), m_Tag(nullptr), m_Transform(nullptr)
		{}
	public:
		EntityID GetID() { return m_ID; }
		ComponentMask GetMask() { return m_Components; }

		Transform* GetTransform() { return m_Transform; }
		Tag* GetTag() { return m_Tag; }

		template <typename T>
		inline T* AddComponent() { return Scene::AddComponent<T>(m_ID); }
		template <typename T>
		inline T* GetComponent() { return Scene::GetComponent<T>(m_ID); }
		template <typename T>
		inline void RemoveComponent() { Scene::RemoveComponent<T>(m_ID); }

		virtual void OnCollision2D(const Collision2D& collision) {}
		
		static inline Entity* CreateEntity() { return Scene::CreateEntity<Entity>(); }
	protected:
		EntityID m_ID;
		ComponentMask m_Components;

		Transform* m_Transform;
		Tag* m_Tag;

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(Timestep ts) {}
		virtual void OnFixedUpdate(Timestep ts) {}
		virtual void OnEvent(Events::Event& e) {}
 	};
}