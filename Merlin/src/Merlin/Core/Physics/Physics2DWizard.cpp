
#include "mlpch.h"
#include "Physics2DWizard.h"

#include "Impulse2D.h"
#include "VelocitySolver2D.h"
#include "SmoothPosition2D.h"

#include <Merlin/Core/Constants.h>
#include <Merlin/Core/Math/Math.h>

namespace Merlin
{
	Physics2DWizard::Physics2DWizard()
	{
		// Physics Solvers
		AddSolver(new VelocitySolver2D());

		// Collision Solvers
		AddSolver(new Impulse2D());
		AddSolver(new SmoothPosition2D());
	}

	Physics2DWizard::~Physics2DWizard()
	{
		for (PhysicsSolver2D* solver : m_PhysicsSolvers)
			delete solver;

		for (CollisionSolver2D* solver : m_CollisionSolvers)
			delete solver;
	}

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
			std::vector<Collision2D*> collisions;

			for (Entity* ent2 : EntityList<BoxCollider2D>())
			{
				BoxCollider2D* col2 = ent2->GetComponent<BoxCollider2D>();

				if (col1 == col2) continue;

				if (CheckCollision(col1, ent1->GetTransform(), col2, ent2->GetTransform()))
				{
					static const Vector2 faces[4] =
					{
						Vector2(-1, 0),
						Vector2(1, 0),
						Vector2(0, -1),
						Vector2(0, 1)
					};

					Vector2 maxA = ent1->GetTransform()->position + col1->size;
					Vector2 minA = ent1->GetTransform()->position - col1->size;

					Vector2 maxB = ent2->GetTransform()->position + col2->size;
					Vector2 minB = ent2->GetTransform()->position - col2->size;

					float distances[4] =
					{
						maxB.x - minA.x,
						maxA.x - minB.x,
						maxB.y - minA.y,
						maxA.y - minB.y
					};

					float penetration = FLT_MAX;
					Vector2 bestAxis;

					for (int i = 0; i < 4; i++)
					{
						if (distances[i] < penetration)
						{
							penetration = distances[i];
							bestAxis = faces[i];
						}
					}

					Collision2D* collision = new Collision2D(ent1, ent2, bestAxis, penetration);

					ent1->OnCollision2D(*collision);

					if (Scene::IsEntityValid(ent1->GetID()) && Scene::IsEntityValid(ent2->GetID()) &&
						ent1->GetComponent<RigidBody2D>()->bodyType != RigidBody2D::PhysicsBody::Kinematic &&
						ent2->GetComponent<RigidBody2D>()->bodyType != RigidBody2D::PhysicsBody::Kinematic)
					{
						collisions.push_back(collision);
					}
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