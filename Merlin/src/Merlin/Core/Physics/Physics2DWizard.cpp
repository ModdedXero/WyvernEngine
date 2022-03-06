#include "mlpch.h"
#include "Physics2DWizard.h"

namespace Merlin
{
	void Physics2DWizard::OnUpdate(Timestep ts) const
	{
		for (Entity* ent : EntityList<RigidBody2D>())
		{
			RigidBody2D* rb = ent->GetComponent<RigidBody2D>();
			Transform* transform = ent->GetTransform();

			rb->force += m_GravityScale * rb->mass;
			rb->velocity += rb->force / rb->mass * ts.GetDeltaTime();
			if (rb->velocity.y > m_MaxGravity)
			{
				rb->velocity.y = m_MaxGravity;
			}

			transform->position += rb->velocity * ts.GetDeltaTime();
			rb->force = Vector3();
		}

		for (Entity* ent1 : EntityList<BoxCollider2D>())
		{
			BoxCollider2D* col1 = ent1->GetComponent<BoxCollider2D>();

			for (Entity* ent2 : EntityList<BoxCollider2D>())
			{
				BoxCollider2D* col2 = ent2->GetComponent<BoxCollider2D>();

				if (col1 == col2) break;

				if (CheckCollision(col1, ent1->GetTransform(), col2, ent2->GetTransform()))
				{
					ent1->OnCollision2D({ ent1->GetTransform(), ent2->GetTransform(), ent1->GetTag(), ent2->GetTag(), Vector2() });
					ent2->OnCollision2D({ ent2->GetTransform(), ent1->GetTransform(), ent2->GetTag(), ent1->GetTag(), Vector2() });
				}
			}
		}
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