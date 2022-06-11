#pragma once

#include <Wyvern/Core/Math/Vector.h>
#include <Wyvern/Core/Scene/NativeScriptComponent.h>
#include <Wyvern/Core/Physics/Physics.h>

namespace Wyvern
{
	struct RigidBody2D : public NativeScriptComponent<RigidBody2D, float, float, float, PhysicsBody>
	{
		RigidBody2D() {}
		~RigidBody2D() {}

		Vector2 velocity;
		Vector2 force;

		PhysicsBody bodyType = PhysicsBody::Dynamic;

		float mass = 1.0f;
		float GetInvMass() { return mass == 0 ? 0 : 1.0f / mass; }

		float drag = 0.05f;
		float bounce = 0.2f;

		virtual void DrawEditor() override;
	};
}