#pragma once

#include <bitset>

namespace Merlin
{
	const size_t MaxEntities = 1000;

	const size_t MaxComponents = 32;
	typedef std::bitset<MaxComponents> ComponentMask;

	typedef unsigned int EntityIndex;
	typedef unsigned int EntityVersion;
	typedef unsigned long long EntityID;

	class Entity
	{
		friend class Scene;
	public:
		Entity(EntityID id, ComponentMask components)
			: m_ID(id), m_Components(components)
		{
		}

		EntityID GetID() { return m_ID; }
		ComponentMask GetMask() { return m_Components; }

		template <typename T>
		T* AddComponent() { return Scene::AddComponent<T>(m_ID); }
		template <typename T>
		T* GetComponent() { return Scene::GetComponent<T>(m_ID); }
		template <typename T>
		void RemoveComponent() { Scene::RemoveComponent<T>(m_ID); }
	private:
		EntityID m_ID;
		ComponentMask m_Components;
	};
}