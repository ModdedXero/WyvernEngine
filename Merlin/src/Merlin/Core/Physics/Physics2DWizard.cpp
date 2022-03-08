
#include "mlpch.h"
#include "Physics2DWizard.h"

#include <Merlin/Core/Constants.h>
#include <Merlin/Core/Math/Math.h>

namespace Merlin
{
	void Physics2DWizard::OnUpdate(Timestep ts) const
	{
		for (Entity* ent : EntityList<RigidBody2D>())
		{
			for (PhysicsSolver2D* solver : m_PhysicsSolvers)
				solver->Solve(ent->GetComponent<RigidBody2D>(), ts, ent->GetTransform());
		}

		for (Entity* ent1 : EntityList<BoxCollider2D>())
		{
			BoxCollider2D* col1 = ent1->GetComponent<BoxCollider2D>();
			std::vector<Collision2D> collisions;

			for (Entity* ent2 : EntityList<BoxCollider2D>())
			{
				BoxCollider2D* col2 = ent2->GetComponent<BoxCollider2D>();

				if (col1 == col2) continue;

				if (CheckCollision(col1, ent1->GetTransform(), col2, ent2->GetTransform()))
				{
					Vector2 normal = ent2->GetTransform()->position - ent1->GetTransform()->position;

					Collision2D collision = { ent1, ent2, normal.Normalize(), 0.0f};

					ent1->OnCollision2D(collision);

					if (Scene::IsEntityValid(ent1->GetID()) && Scene::IsEntityValid(ent2->GetID()))
						collisions.push_back(collision);
				}
			}

			for (CollisionSolver2D* solver : m_CollisionSolvers)
				solver->Solve(collisions);
		}
	}

	void Physics2DWizard::AddSolver(CollisionSolver2D* solver)
	{
		m_CollisionSolvers.push_back(solver);
	}

	void Physics2DWizard::AddSolver(PhysicsSolver2D* solver)
	{
		m_PhysicsSolvers.push_back(solver);
	}

	bool Physics2DWizard::CheckCollision(
		const BoxCollider2D* boxCollider,
		const Transform* transform,
		const BoxCollider2D* otherCollider,
		const Transform* otherTransform)
	{
		return (transform->position.x - boxCollider->size.x < otherTransform->position.x + otherCollider->size.x &&
			transform->position.x + boxCollider->size.x > otherTransform->position.x - otherCollider->size.x &&
			transform->position.y - boxCollider->size.y < otherTransform->position.y + otherCollider->size.y &&
			transform->position.y + boxCollider->size.y > otherTransform->position.y - otherCollider->size.y);
	}
}