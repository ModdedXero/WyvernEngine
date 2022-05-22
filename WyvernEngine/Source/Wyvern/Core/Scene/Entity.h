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
		Entity(EntityRegister& view);

		UUID GetUUID() const;
		SceneID GetSceneID() const;
		Ref<Scene> GetScene() const;
		Entity GetParent() const;
		std::vector<UUID> GetChildren() const;

		Tag* GetTag();
		Transform* GetTransform();
		std::vector<Component*> GetComponents();

		void AddChildEntity(EntityRegister& entity);
		void RemoveChildEntity(EntityRegister& entity);

		void DestroyEntity();

		bool IsValid();

		bool operator ==(const Entity& rhs)
		{
			return m_EntityRegister.UniqueID == rhs.m_EntityRegister.UniqueID;
		}

		operator EntityRegister&()
		{
			return m_EntityRegister;
		}

		operator UUID& ()
		{
			return m_EntityRegister.UniqueID;
		}

	private:
		EntityRegister m_EntityRegister;
 	};
}