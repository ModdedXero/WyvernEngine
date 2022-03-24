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
			BoxCollider2D* collider,
			Transform* transform,
			BoxCollider2D* otherCollider,
			Transform* otherTransform);

		static bool CheckCollision(
			BoxCollider2D* collider,
			Transform* transform,
			SphereCollider2D* otherCollider,
			Transform* otherTransform);

		static Collision2D* GetCollisionData(Entity* ent, BoxCollider2D* collider, Entity* otherEnt, BoxCollider2D* otherCollider);
		static Collision2D* GetCollisionData(Entity* ent, BoxCollider2D* collider, Entity* otherEnt, SphereCollider2D* otherCollider);
		static Collision2D* GetCollisionData(Entity* ent, SphereCollider2D* collider, Entity* otherEnt, BoxCollider2D* otherCollider);
	};
}