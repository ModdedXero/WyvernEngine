#pragma once

namespace Merlin
{
	class Scene;
	class Entity;
	struct Transform;
	struct Tag;

	struct Component
	{
		friend class Scene;
	public:
		Component()
			: m_Entity(nullptr), m_Transform(nullptr), m_Tag(nullptr)
		{}

		virtual ~Component() = 0;

		Entity* GetEntity() const { return m_Entity; }
		Transform* GetTransform() const { return m_Transform; }
		Tag* GetTag() const { return m_Tag; }
	private:
		Entity* m_Entity;
		Transform* m_Transform;
		Tag* m_Tag;
	};
}