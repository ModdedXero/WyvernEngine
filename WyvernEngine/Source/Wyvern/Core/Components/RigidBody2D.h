#pragma once

#include <Wyvern/Core/Math/Vector.h>
#include <Wyvern/Core/Scene/Component.h>

namespace Wyvern
{
	enum class PhysicsBody
	{
		Dynamic = 0,
		Kinematic = 1,
		Static = 2
	};

	struct RigidBody2D : public Component
	{
		RigidBody2D() {}
		~RigidBody2D() {}

		Vector2 velocity;
		Vector2 force;

		PhysicsBody bodyType = (PhysicsBody)m_BodyType;

		float mass = 1.0f;
		float GetInvMass() { return mass == 0 ? 0 : 1.0f / mass; }

		float drag = 0.05f;
		float bounce = 0.2f;
		int m_BodyType = 0;

		WV_SERIALIZE_COMPONENT(RigidBody2D)
		WV_SERIALIZE_VARIABLE(float, mass)
		WV_SERIALIZE_VARIABLE(float, drag)
		WV_SERIALIZE_VARIABLE(float, bounce)
		WV_SERIALIZE_COMPONENT_END
	};
}