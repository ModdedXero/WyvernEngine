#pragma once

#include <Merlin/Scene/Tag.h>
#include <Merlin/Scene/Transform.h>
#include <Merlin/Core/Physics/Collider2D.h>

#include <bitset>

namespace Merlin
{
	const size_t MaxEntities = 50000;

	const size_t MaxComponents = 32;
	typedef std::bitset<MaxComponents> ComponentMask;

	typedef unsigned int EntityIndex;
	typedef unsigned int EntityVersion;
	typedef unsigned long long EntityID;

	class Entity
	{
		friend class Scene;
	protected:
		Entity(EntityID id, ComponentMask components)
			: m_ID(id), m_Components(components), m_Transform(nullptr), m_Tag(nullptr)
		{
		}

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

		static Entity* CreateEntity();
	protected:
		EntityID m_ID;
		ComponentMask m_Components;

		Transform* m_Transform;
		Tag* m_Tag;

		virtual void InitDefaultComponents() {}
	};
}