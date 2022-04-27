#pragma once

#include <Wyvern/Core/Math/Vector.h>
#include <Wyvern/Core/Scene/Component.h>

namespace Wyvern
{
	struct RigidBody2D : public Component
	{
		RigidBody2D() {}
		~RigidBody2D() {}

		Vector2 velocity;
		Vector2 force;

		enum class PhysicsBody
		{
			Dynamic = 0,
			Kinematic = 1,
			Static = 2
		} bodyType = PhysicsBody::Dynamic;

		float mass = 1.0f;
		float GetInvMass() { return mass == 0 ? 0 : 1.0f / mass; }

		float drag = 0.05f;
		float bounce = 0.2f;
	};
}