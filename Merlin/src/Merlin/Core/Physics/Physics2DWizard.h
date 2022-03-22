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

		void OnFixedUpdate(Timestep ts) override;

		void AddSolver(CollisionSolver2D* solver);
		void AddSolver(PhysicsSolver2D* solver);
	private:
		std::vector<CollisionSolver2D*> m_CollisionSolvers;
		std::vector<PhysicsSolver2D*> m_PhysicsSolvers;

		static bool CheckCollision(
			const BoxCollider2D* collider,
			const Transform* transform,
			const BoxCollider2D* otherCollider,
			const Transform* otherTransform);

		static bool CheckCollision(
			const BoxCollider2D* collider,
			const Transform* transform,
			const SphereCollider2D* otherCollider,
			const Transform* otherTransform);

		static Collision2D* GetCollisionData(Entity* ent1, BoxCollider2D* col1, Entity* ent2, BoxCollider2D* col2);
		static Collision2D* GetCollisionData(Entity* ent1, BoxCollider2D* col1, Entity* ent2, SphereCollider2D* col2);
		static Collision2D* GetCollisionData(Entity* ent1, SphereCollider2D* col1, Entity* ent2, BoxCollider2D* col2);
	};
}