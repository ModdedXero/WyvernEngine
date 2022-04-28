#pragma once

#include <Wyvern/Core/Scene/Component.h>
#include <Wyvern/Core/Math/Math.h>
#include <Wyvern/Core/ApplicationDomain.h>

namespace Wyvern
{
	class Entity;

	struct Transform : public Component
	{
		Transform() {}
		~Transform() {}

		
		Vector3 position;
		Vector3 rotation;
		Vector3 scale = Vector3(1, 1, 1);

		Vector3 GlobalPosition();
		Vector3 GlobalRotation();
		Vector3 GlobalScale();

		Matrix4x4 GetTransform();
		Matrix4x4 GetGlobalTransform();

		virtual void Serialize(YAML::Emitter& out) override;
		virtual void Deserialize(Entity* ent, YAML::Node& data) override;
		virtual void DrawEditor() override;

		static std::shared_ptr<Component> RegisterComponent() { return std::make_shared<Transform>(); }
		static inline bool IsRegistered = ApplicationDomain::RegisterComponent("Transform", RegisterComponent);
	};
}