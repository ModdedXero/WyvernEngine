#pragma once

#include <Merlin/Scene/Scene.h>

#include <bitset>

namespace Merlin
{
	const size_t MaxComponents = 32;
	typedef std::bitset<MaxComponents> ComponentMask;

	typedef unsigned int EntityID;

	class Entity
	{
	public:
		EntityID GetID() const { return m_ID; }

		template <typename T>
		static T* AddComponent() { return Scene::AddComponent(m_ID); }
		template <typename T>
		static T* GetComponent() { return Scene::GetComponent(m_ID); }
		template <typename T>
		static void RemoveComponent() { Scene::RemoveComponent(m_ID); }
	private:
		EntityID m_ID;
		ComponentMask m_Components;
	};
}