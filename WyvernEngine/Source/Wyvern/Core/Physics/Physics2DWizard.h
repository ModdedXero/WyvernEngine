#pragma once

#include "Collider2D.h"
#include "CollisionSolver2D.h"
#include "PhysicsSolver2D.h"

#include <Wyvern/Core/Scene/Wizard.h>
#include <Wyvern/Core/Components/RigidBody2D.h>

namespace Wyvern
{
	class Physics2DWizard : public Wizard
	{
	public:
		Physics2DWizard();
		~Physics2DWizard();

		void OnFixedUpdate() override;

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

		static Ref<Collision2D> GetCollisionData(Entity* entity, BoxCollider2D* collider, Entity* otherEnt, BoxCollider2D* otherCollider);
		static Ref<Collision2D> GetCollisionData(Entity* entity, BoxCollider2D* collider, Entity* otherEnt, SphereCollider2D* otherCollider);
		static Ref<Collision2D> GetCollisionData(Entity* entity, SphereCollider2D* collider, Entity* otherEnt, BoxCollider2D* otherCollider);
	};
}