
#include "wvpch.h"
#include "Physics2DWizard.h"

#include "Impulse2D.h"
#include "VelocitySolver2D.h"
#include "SmoothPosition2D.h"

#include <Wyvern/Core/Scene/EntityList.h>
#include <Wyvern/Core/Constants.h>
#include <Wyvern/Core/Math/Math.h>

namespace Wyvern
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

	void Physics2DWizard::OnFixedUpdate()
	{
		for (Entity entity : EntityList<RigidBody2D>(Scene::GetActiveScene()))
		{
			for (PhysicsSolver2D* solver : m_PhysicsSolvers)
				solver->Solve(Scene::GetComponent<RigidBody2D>(entity), entity.GetTransform());
		}

		std::vector<Collision2D> collisions;

		for (Entity ent1 : EntityList<BoxCollider2D>(Scene::GetActiveScene()))
		{
			BoxCollider2D* col1 = Scene::GetComponent<BoxCollider2D>(ent1);
			RigidBody2D* rb1 = Scene::GetComponent<RigidBody2D>(ent1);

			for (Entity ent2 : EntityList<BoxCollider2D>(Scene::GetActiveScene()))
			{
				BoxCollider2D* col2 = Scene::GetComponent<BoxCollider2D>(ent2);
				RigidBody2D* rb2 = Scene::GetComponent<RigidBody2D>(ent2);

				if (col1 == col2) continue;

				if (CheckCollision(col1, ent1.GetTransform(), col2, ent2.GetTransform()))
				{
					if (Scene::IsEntityValid(ent1) && Scene::IsEntityValid(ent2) &&
						rb1->bodyType != PhysicsBody::Kinematic &&
						rb2->bodyType != PhysicsBody::Kinematic &&
						!(rb1->bodyType == PhysicsBody::Static &&
							rb2->bodyType == PhysicsBody::Static))
					{
						Collision2D collision = GetCollisionData(ent1, col1, ent2, col2);

						collisions.push_back(collision);

						for (NativeComponentBase* nsc : Scene::GetComponentsOfBase<NativeComponentBase>(ent1))
						{
							nsc->OnCollision2D(collision);
						}
					}
				}
			}
		}

		for (Entity ent1 : EntityList<BoxCollider2D>(Scene::GetActiveScene()))
		{
			BoxCollider2D* col1 = Scene::GetComponent<BoxCollider2D>(ent1);

			for (Entity ent2 : EntityList<SphereCollider2D>(Scene::GetActiveScene()))
			{
				SphereCollider2D* col2 = Scene::GetComponent<SphereCollider2D>(ent2);

				if (CheckCollision(col1, ent1.GetTransform(), col2, ent2.GetTransform()))
				{
					if (Scene::IsEntityValid(ent1) && Scene::IsEntityValid(ent2) &&
						Scene::GetComponent<RigidBody2D>(ent1)->bodyType != PhysicsBody::Kinematic &&
						Scene::GetComponent<RigidBody2D>(ent2)->bodyType != PhysicsBody::Kinematic)
					{
						// Box vs Sphere
						Collision2D collision = GetCollisionData(ent1, col1, ent2, col2);

						collisions.push_back(collision);

						for (NativeComponentBase* nsc : Scene::GetComponentsOfBase<NativeComponentBase>(ent1))
						{
							nsc->OnCollision2D(collision);
						}

						// Sphere vs Box
						Collision2D collisionOther = GetCollisionData(ent2, col2, ent1, col1);

						collisions.push_back(collisionOther);

						for (NativeComponentBase* nsc : Scene::GetComponentsOfBase<NativeComponentBase>(ent2))
						{
							nsc->OnCollision2D(collisionOther);
						}
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
		return (transform->GlobalPosition().x - collider->size.x < otherTransform->GlobalPosition().x + otherCollider->size.x &&
			transform->GlobalPosition().x + collider->size.x > otherTransform->GlobalPosition().x - otherCollider->size.x &&
			transform->GlobalPosition().y - collider->size.y < otherTransform->GlobalPosition().y + otherCollider->size.y &&
			transform->GlobalPosition().y + collider->size.y > otherTransform->GlobalPosition().y - otherCollider->size.y);
	}

	bool Physics2DWizard::CheckCollision(
		BoxCollider2D* collider,
		Transform* transform,
		SphereCollider2D* otherCollider,
		Transform* otherTransform)
	{
		Vector2 delta = otherTransform->GlobalPosition() - transform->GlobalPosition();
		Vector2 closest = Mathf::Clamp(delta, -collider->size, collider->size);
		Vector2 localPoint = delta - closest;

		return localPoint.Length() < otherCollider->radius;
	}

	Collision2D Physics2DWizard::GetCollisionData(Entity entity, BoxCollider2D* collider, Entity otherEnt, BoxCollider2D* otherCollider)
	{
		static const Vector2 faces[4] =
		{
			Vector2(-1, 0),
			Vector2(1, 0),
			Vector2(0, -1),
			Vector2(0, 1)
		};

		Vector2 maxA = entity.GetTransform()->GlobalPosition() + collider->size;
		Vector2 minA = entity.GetTransform()->GlobalPosition() - collider->size;

		Vector2 maxB = otherEnt.GetTransform()->GlobalPosition() + otherCollider->size;
		Vector2 minB = otherEnt.GetTransform()->GlobalPosition() - otherCollider->size;

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

		return Collision2D(entity, otherEnt, bestAxis, penetration);
	}

	Collision2D Physics2DWizard::GetCollisionData(Entity entity, BoxCollider2D* collider, Entity otherEnt, SphereCollider2D* otherCollider)
	{
		Vector2 delta = otherEnt.GetTransform()->GlobalPosition() - entity.GetTransform()->GlobalPosition();
		Vector2 closest = Mathf::Clamp(delta, -collider->size, collider->size);
		Vector2 localPoint = delta - closest;

		float distance = localPoint.Length();

		Vector2 normal = localPoint.Normalize();
		float penetration = otherCollider->radius - distance;

		return Collision2D(entity, otherEnt, normal, penetration);
	}

	Collision2D Physics2DWizard::GetCollisionData(Entity entity, SphereCollider2D* collider, Entity otherEnt, BoxCollider2D* otherCollider)
	{
		Vector2 delta = entity.GetTransform()->GlobalPosition() - otherEnt.GetTransform()->GlobalPosition();
		Vector2 closest = Mathf::Clamp(delta, -otherCollider->size, otherCollider->size);
		Vector2 localPoint = delta - closest;

		float distance = localPoint.Length();

		Vector2 normal = localPoint.Normalize();
		float penetration = collider->radius - distance;

		return Collision2D(entity, otherEnt, -normal, penetration);
	}
}