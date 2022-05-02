#pragma once

#include <Wyvern/Core/Math/Vector.h>
#include <Wyvern/Core/Scene/SceneSerializer.h>

#include <yaml-cpp/yaml.h>

namespace Wyvern
{
	class Entity;
	struct Transform;
	struct Tag;
	struct SerializeInfo;

	struct Component
	{
		Component()
			: m_Entity(nullptr), m_Transform(nullptr), m_Tag(nullptr)
		{}
		virtual ~Component() = 0;

		Entity* GetEntity() const { return m_Entity; }
		Transform* GetTransform() const { return m_Transform; }
		Tag* GetTag() const { return m_Tag; }
		int GetID() { return m_ComponentID; }

		virtual void __Serialize(SerializeInfo& info) {}
		virtual void Serialize(YAML::Emitter& out) {}
		virtual void Deserialize(Entity* ent, YAML::Node& data) {}
		virtual void AddToEntity(Entity* ent) {}
		virtual void DrawEditor() {}
	private:
		Entity* m_Entity;
		Transform* m_Transform;
		Tag* m_Tag;

		int m_ComponentID;

		friend class Scene;
		friend class ApplicationDomain;

		typedef Component base;
		typedef Component type;
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