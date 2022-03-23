
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

	void Physics2DWizard::OnFixedUpdate(Timestep ts)
	{
		for (Entity* ent : EntityList<RigidBody2D>())
		{
			for (PhysicsSolver2D* solver : m_PhysicsSolvers)
				solver->Solve(ent->GetComponent<RigidBody2D>(), ts, ent->GetTransform());
		}

		std::vector<Collision2D*> collisions;

		for (Entity* ent1 : EntityList<BoxCollider2D>())
		{
			BoxCollider2D* col1 = ent1->GetComponent<BoxCollider2D>();
			RigidBody2D* rb1 = ent1->GetComponent<RigidBody2D>();

			for (Entity* ent2 : EntityList<BoxCollider2D>())
			{
				BoxCollider2D* col2 = ent2->GetComponent<BoxCollider2D>();
				RigidBody2D* rb2 = ent2->GetComponent<RigidBody2D>();

				if (col1 == col2) continue;

				if (CheckCollision(col1, ent1->GetTransform(), col2, ent2->GetTransform()))
				{
					if (Scene::IsEntityValid(ent1->GetID()) && Scene::IsEntityValid(ent2->GetID()) &&
						rb1->bodyType != RigidBody2D::PhysicsBody::Kinematic &&
						rb2->bodyType != RigidBody2D::PhysicsBody::Kinematic &&
						!(rb1->bodyType == RigidBody2D::PhysicsBody::Static &&
							rb2->bodyType == RigidBody2D::PhysicsBody::Static))
					{
						Collision2D* collision = GetCollisionData(ent1, col1, ent2, col2);

						ent1->OnCollision2D(*collision);
						collisions.push_back(collision);
					}
				}
			}
		}

		for (Entity* ent1 : EntityList<BoxCollider2D>())
		{
			BoxCollider2D* col1 = ent1->GetComponent<BoxCollider2D>();

			for (Entity* ent2 : EntityList<SphereCollider2D>())
			{
				SphereCollider2D* col2 = ent2->GetComponent<SphereCollider2D>();

				if (CheckCollision(col1, ent1->GetTransform(), col2, ent2->GetTransform()))
				{
					if (Scene::IsEntityValid(ent1->GetID()) && Scene::IsEntityValid(ent2->GetID()) &&
						ent1->GetComponent<RigidBody2D>()->bodyType != RigidBody2D::PhysicsBody::Kinematic &&
						ent2->GetComponent<RigidBody2D>()->bodyType != RigidBody2D::PhysicsBody::Kinematic)
					{
						// Box vs Sphere
						Collision2D* collision = GetCollisionData(ent1, col1, ent2, col2);

						ent1->OnCollision2D(*collision);
						collisions.push_back(collision);

						// Sphere vs Box
						Collision2D* collisionOther = GetCollisionData(ent2, col2, ent1, col1);

						ent2->OnCollision2D(*collisionOther);
						collisions.push_back(collisionOther);
					}
				}
			}
		}

		for (CollisionSolver2D* solver : m_CollisionSolvers)
			solver->Solve(collisions);
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
		BoxCollider2D* collider,
		Transform* transform,
		BoxCollider2D* otherCollider,
		Transform* otherTransform)
	{
		return (transform->position.x - collider->size.x < otherTransform->position.x + otherCollider->size.x &&
			transform->position.x + collider->size.x > otherTransform->position.x - otherCollider->size.x &&
			transform->position.y - collider->size.y < otherTransform->position.y + otherCollider->size.y &&
			transform->position.y + collider->size.y > otherTransform->position.y - otherCollider->size.y);
	}

	bool Physics2DWizard::CheckCollision(
		BoxCollider2D* collider,
		Transform* transform,
		SphereCollider2D* otherCollider,
		Transform* otherTransform)
	{
		Vector2 delta = otherTransform->GetNormalPosition() - transform->GetNormalPosition();
		Vector2 clamped = Functions::Clamp(delta, -collider->size, collider->size);
		Vector2 closest = transform->GetNormalPosition() + clamped;

		delta = closest - otherTransform->GetNormalPosition();

		return delta.Length() < otherCollider->radius;
	}

	Collision2D* Physics2DWizard::GetCollisionData(Entity* ent1, BoxCollider2D* col1, Entity* ent2, BoxCollider2D* col2)
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

		return new Collision2D(ent1, ent2, bestAxis, penetration);
	}

	Collision2D* Physics2DWizard::GetCollisionData(Entity* ent1, BoxCollider2D* col1, Entity* ent2, SphereCollider2D* col2)
	{
		Vector2 delta = ent2->GetTransform()->GetNormalPosition() - ent1->GetTransform()->GetNormalPosition();
		Vector2 clamped = Functions::Clamp(delta, -col1->size / 2, col1->size / 2);
		Vector2 closest = ent1->GetTransform()->GetNormalPosition() + clamped;
		Vector2 localPoint = delta - closest;

		float distance = localPoint.Length();

		Vector2 normal = localPoint.Normalize();
		float penetration = col2->radius - distance;

		return new Collision2D(ent1, ent2, normal, penetration);
	}

	Collision2D* Physics2DWizard::GetCollisionData(Entity* ent1, SphereCollider2D* col1, Entity* ent2, BoxCollider2D* col2)
	{
		Vector2 delta = ent1->GetTransform()->GetNormalPosition() - ent2->GetTransform()->GetNormalPosition();
		Vector2 clamped = Functions::Clamp(delta, -col2->size / 2, col2->size / 2);
		Vector2 closest = ent1->GetTransform()->GetNormalPosition() + clamped;
		Vector2 localPoint = delta - closest;

		float distance = localPoint.Length();

		Vector2 normal = localPoint.Normalize();
		float penetration = col1->radius - distance;

		return new Collision2D(ent1, ent2, -normal, penetration);
	}
}