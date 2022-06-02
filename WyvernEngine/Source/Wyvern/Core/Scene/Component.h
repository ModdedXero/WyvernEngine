#pragma once

#include "Entity.h"

#include <Wyvern/Core/Math/Vector.h>
#include <Wyvern/Core/Scene/Serializer.h>
#include <Wyvern/Core/Physics/Collision2D.h>

#include <yaml-cpp/yaml.h>

namespace Wyvern
{
	struct Transform;
	struct Tag;
	struct SerializeInfo;

	struct Component
	{
	private:
		friend class Scene;
		friend class ApplicationDomain;

	public:
		Component() {}
		virtual ~Component() = 0;

		Entity& GetEntity() { return m_Entity; }
		Tag* GetTag() { return m_Entity.GetTag(); }
		Transform* GetTransform() { return m_Entity.GetTransform(); }
		int GetSceneID() { return m_ComponentID; }

		virtual void __Serialize(SerializeInfo& info) {}
		virtual void Serialize(YAML::Emitter& out) {}
		virtual void Deserialize(Entity entity, YAML::Node& data) {}
		virtual void DrawEditor() {}

	private:
		Entity m_Entity;

		int m_ComponentID;

		typedef Component base;
		typedef Component type;
	};

	struct NativeScriptComponent : public Component
	{
	private:
		friend class Scene;
		friend class ApplicationDomain;

	public:
		NativeScriptComponent()
			: Component()
		{}
		virtual ~NativeScriptComponent() = 0;

		virtual void OnAttach() {}
		virtual void OnDestroy() {}
		virtual void OnUpdate() {}
		virtual void OnFixedUpdate() {}

		virtual void OnCollision2D(const Collision2D& collision) {}

	private:
		typedef NativeScriptComponent base;
	};
}