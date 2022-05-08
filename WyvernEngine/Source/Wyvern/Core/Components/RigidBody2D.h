#pragma once

#include <Wyvern/Core/Math/Vector.h>
#include <Wyvern/Core/Scene/Component.h>
#include <Wyvern/Core/Physics/Physics.h>

namespace Wyvern
{
	struct RigidBody2D : public Component
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

		WV_SERIALIZE_COMPONENT(RigidBody2D)
		WV_SERIALIZE_VARIABLE(float, mass)
		WV_SERIALIZE_VARIABLE(float, drag)
		WV_SERIALIZE_VARIABLE(float, bounce)
		WV_SERIALIZE_VARIABLE(PhysicsBody, bodyType)
		WV_SERIALIZE_COMPONENT_END
	};
}