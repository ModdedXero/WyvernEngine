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
			RigidBody2D* rb = ent->GetComponent<RigidBody2D>();
			if (rb->isStatic) continue;

			Transform* transform = ent->GetTransform();

			rb->force += GravityScale * rb->mass;
			rb->velocity += (rb->force / rb->mass) * ts.GetDeltaTime();
			if (rb->velocity.y > MaxGravity)
			{
				rb->velocity.y = MaxGravity;
			}

			transform->position += rb->velocity * ts.GetDeltaTime();
			rb->force = Vector3();
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
					float penetration = GetPenetration(col1, ent1->GetTransform(), col2, ent2->GetTransform());
					Vector2 normal = GetNormal((Vector2&)(ent2->GetTransform()->position - ent1->GetTransform()->position));

					Collision2D collision = { ent1->GetID(), ent2->GetID(), normal, penetration };

					collisions.push_back(collision);
					ent1->OnCollision2D(collision);
				}
			}

			for (Physics2DSolver* solver : m_Solvers)
				solver->Solve(collisions);
		}
	}

	void Physics2DWizard::AddSolver(Physics2DSolver* solver)
	{
		m_Solvers.push_back(solver);
	}

	Vector2 Physics2DWizard::GetNormal(Vector2& target)
	{
		Vector2 directions[] = {
			Vector2(0, 1),
			Vector2(1, 0),
			Vector2(0, -1),
			Vector2(-1, 0)
		};

		float max = 0.0f;
		unsigned int bestMatch = -1;
		for (unsigned int i = 0; i < 4; i++)
		{
			float dot = Vector2::Dot(target.Normalize(), directions[i]);
			if (dot > max)
			{
				max = dot;
				bestMatch = i;
			}
		}

		return directions[bestMatch];
	}

	float Physics2DWizard::GetPenetration(BoxCollider2D* box1, Transform* ts1, BoxCollider2D* box2, Transform* ts2)
	{
		Vector2 difference = ts1->position - ts2->position;
		Vector2 clamped = Functions::Clamp(difference, -box2->size, box2->size);
		Vector2 closest = ts2->position + clamped;

		Vector2 distance = closest - ts1->position;
		Vector2 penetration = distance - box1->size;
		return penetration.Length();
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