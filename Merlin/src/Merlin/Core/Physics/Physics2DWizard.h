
#pragma once

#include "RigidBody2D.h"
#include "Collider2D.h"
#include "CollisionSolver2D.h"
#include "PhysicsSolver2D.h"

#include <Merlin/Core/Scene/Wizard.h>

namespace Merlin
{
	class Physics2DWizard : public Wizard
	{
	public:
		Physics2DWizard();
		~Physics2DWizard();

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