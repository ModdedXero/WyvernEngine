#include "SmoothPosition2D.h"

#include <Merlin/Core/Constants.h>
#include <Merlin/Scene/Scene.h>
#include <Merlin/Core/Physics/RigidBody2D.h>

namespace Merlin
{
	void SmoothPosition2D::Solve(const std::vector<Collision2D> collisions)
	{
		for (Collision2D collision : collisions)
		{
			RigidBody2D* rbA = Scene::GetComponent<RigidBody2D>(collision.entityA);
			RigidBody2D* rbB = Scene::GetComponent<RigidBody2D>(collision.entityB);
		}
	}
}