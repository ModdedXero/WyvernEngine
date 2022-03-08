
#pragma once

#include <Merlin/Scene/Wizard.h>
#include <Merlin/Core/Physics/RigidBody2D.h>
#include <Merlin/Core/Physics/Collider2D.h>
#include <Merlin/Core/Physics/CollisionSolver2D.h>
#include <Merlin/Core/Physics/PhysicsSolver2D.h>

#include <Merlin/Core/Physics/PushSolver2D.h>
#include <Merlin/Core/Physics/Impulse2D.h>

namespace Merlin
{
	class Physics2DWizard : public Wizard
	{
	public:
		Physics2DWizard()
		{
			AddSolver(new Impulse2D());
			AddSolver(new PushSolver2D());
		}

		void OnUpdate(Timestep ts) const override;

		void AddSolver(CollisionSolver2D* solver);
		void AddSolver(PhysicsSolver2D* solver);
	private:
		std::vector<CollisionSolver2D*> m_CollisionSolvers;
		std::vector<PhysicsSolver2D*> m_PhysicsSolvers;

		static bool CheckCollision(
			const BoxCollider2D* boxCollider,
			const Transform* transform,
			const BoxCollider2D* otherCollider,
			const Transform* otherTransform);
	};
}