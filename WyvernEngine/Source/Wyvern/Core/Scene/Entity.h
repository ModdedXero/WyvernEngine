#pragma once

#include "UUID.h"
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
		friend class Serializer;
		template <typename... ComponentTypes>
		friend class EntityList;
	protected:
		Entity()
			: m_SceneID(0), m_Tag(nullptr), m_Transform(nullptr), m_Parent(nullptr)
		{}
	public:
		UUID GetUUID() { return m_UUID; }
		SceneID GetSceneID() { return m_SceneID; }

		Transform* GetTransform() { return m_Transform; }
		Tag* GetTag() { return m_Tag; }

		std::vector<Component*> GetAllComponents() { return m_ComponentPtrs; }

		void DestroyEntity();

		void AddChildEntity(Entity* entity);
		void RemoveChildEntity(Entity* entity);

		Entity* GetParent() { return m_Parent; }
		std::vector<Entity*> GetChildren() { return m_Children; }

		virtual void OnCollision2D(Ref<Collision2D> collision) {}
	private:
		UUID m_UUID;
		SceneID m_SceneID;
		Ref<Scene> m_Scene;
		ComponentMask m_Components;

		Transform* m_Transform;
		Tag* m_Tag;

		Entity* m_Parent;
		std::vector<Entity*> m_Children;
		std::vector<Component*> m_ComponentPtrs;
 	};
}