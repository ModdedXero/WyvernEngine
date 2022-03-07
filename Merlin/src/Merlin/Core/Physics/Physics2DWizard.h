#pragma once

#include <Merlin/Scene/Wizard.h>
#include <Merlin/Core/Physics/RigidBody2D.h>
#include <Merlin/Core/Physics/Collider2D.h>
#include <Merlin/Core/Physics/Physics2DSolver.h>
#include <Merlin/Core/Physics/Impulse2D.h>
#include <Merlin/Core/Physics/SmoothPosition2D.h>

namespace Merlin
{
	class Physics2DWizard : public Wizard
	{
	public:
		Physics2DWizard()
		{
			AddSolver(new Impulse2D());
			AddSolver(new SmoothPosition2D());
		}

		void OnUpdate(Timestep ts) const override;

		void AddSolver(Physics2DSolver* solver);
	private:
		std::vector<Physics2DSolver*> m_Solvers;

		static Vector2 GetNormal(Vector2& target);

		static float GetPenetration(BoxCollider2D* box1, Transform* ts1, BoxCollider2D* box2, Transform* ts2);

		static bool CheckCollision(
			const BoxCollider2D* boxCollider,
			const Transform* transform,
			const BoxCollider2D* otherCollider,
			const Transform* otherTransform);
	};
}