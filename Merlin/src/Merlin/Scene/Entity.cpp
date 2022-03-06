#include "mlpch.h"
#include "Entity.h"

#include <Merlin/Scene/Scene.h>
#include <Merlin/Core/Physics/Collider2D.h>

namespace Merlin
{
	Entity* Entity::CreateEntity()
	{
		return Scene::CreateEntity<Entity>();
	}
}