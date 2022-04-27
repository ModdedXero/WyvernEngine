#pragma once

#include <Wyvern/Core/Math/Vector.h>

#include <yaml-cpp/yaml.h>

namespace Wyvern
{
	class Scene;
	class Entity;
	struct Transform;
	struct Tag;

	struct Component
	{
		Component()
			: m_Entity(nullptr), m_Transform(nullptr), m_Tag(nullptr)
		{}
		virtual ~Component() = 0;

		Entity* GetEntity() const { return m_Entity; }
		Transform* GetTransform() const { return m_Transform; }
		Tag* GetTag() const { return m_Tag; }

		virtual void Serialize(YAML::Emitter& out) {}
		virtual void Deserialize(Entity* ent, YAML::Node& data) {}
	private:
		Entity* m_Entity;
		Transform* m_Transform;
		Tag* m_Tag;


		friend class Scene;
		friend class ApplicationDomain;

		typedef Component base;
	};

	struct NativeScriptComponent : public Component
	{
		NativeScriptComponent()
			: Component()
		{}
		virtual ~NativeScriptComponent() = 0;

		virtual void OnAwake() {}
		virtual void OnDestroy() {}
		virtual void OnUpdate() {}

	private:
		friend class Scene;
		friend class ApplicationDomain;

		typedef NativeScriptComponent base;
	};
}