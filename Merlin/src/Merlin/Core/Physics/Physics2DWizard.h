#pragma once

#include <Merlin/Scene/Wizard.h>
#include <Merlin/Core/Physics/RigidBody2D.h>
#include <Merlin/Core/Physics/Collider2D.h>

namespace Merlin
{
	class Physics2DWizard : public Wizard
	{
	public:
		void OnUpdate(Timestep ts) const override;
	private:
		const Vector3 m_GravityScale = Vector3(0, -1.0f, 0);
		const float m_MaxGravity = 4.0f;

		static bool CheckCollision(
			const BoxCollider2D* boxCollider,
			const Transform* transform,
			const BoxCollider2D* otherCollider,
			const Transform* otherTransform);
	};
}