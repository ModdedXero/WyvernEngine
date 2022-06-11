#pragma once

#include "Entity.h"

#include <Wyvern/Core/Object.h>

#include <Wyvern/Core/Math/Vector.h>
#include <Wyvern/Core/Scene/Serializer.h>
#include <Wyvern/Core/Physics/Collision2D.h>

#include <yaml-cpp/yaml.h>

namespace Wyvern
{
	struct Transform;
	struct Tag;
	struct SerializeInfo;

	class ComponentBase : public Object
	{
	private:
		friend class Scene;
		friend class ApplicationDomain;

	public:
		ComponentBase() {}
		virtual ~ComponentBase() = 0;

		Entity& GetEntity() { return m_Entity; }
		Tag* GetTag() { return m_Entity.GetTag(); }
		Transform* GetTransform() { return m_Entity.GetTransform(); }
		int GetSceneID() { return m_ComponentID; }

		virtual void DrawEditor() {}

	private:
		Entity m_Entity;
		int m_ComponentID;

		typedef ComponentBase base;
	};

	class NativeComponentBase : public ComponentBase
	{
	private:
		friend class Scene;
		friend class ApplicationDomain;

	public:
		NativeComponentBase()
			: ComponentBase()
		{}
		virtual ~NativeComponentBase() = 0;

		virtual void OnAttach() {}
		virtual void OnDestroy() {}
		virtual void OnUpdate() {}
		virtual void OnFixedUpdate() {}

		virtual void OnCollision2D(const Collision2D& collision) {}

	private:
		typedef NativeComponentBase base;
	};
}