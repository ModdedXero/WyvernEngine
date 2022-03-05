#pragma once

#include <Merlin/Scene/Transform.h>

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
	private:
		Entity(EntityID id, ComponentMask components)
			: m_ID(id), m_Components(components), m_Transform(nullptr)
		{
		}

	public:
		EntityID GetID() { return m_ID; }
		ComponentMask GetMask() { return m_Components; }
		Transform* GetTransform() { return m_Transform; }

		template <typename T>
		inline T* AddComponent() { return Scene::AddComponent<T>(m_ID); }
		template <typename T>
		inline T* GetComponent() { return Scene::GetComponent<T>(m_ID); }
		template <typename T>
		inline void RemoveComponent() { Scene::RemoveComponent<T>(m_ID); }

		static Entity* CreateEntity();
	private:
		EntityID m_ID;
		ComponentMask m_Components;
		Transform* m_Transform;

		virtual void InitDefaultComponents();
	};
}