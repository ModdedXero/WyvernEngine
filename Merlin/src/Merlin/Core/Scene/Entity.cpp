#include "mlpch.h"
#include "Entity.h"

#include "Scene.h"

namespace Merlin
{
	Entity* Entity::CreateEntity()
	{
		return Scene::CreateEntity<Entity>();
	}
}