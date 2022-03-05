#include "mlpch.h"
#include "Entity.h"

#include <Merlin/Scene/Scene.h>

namespace Merlin
{
	//Transform* Entity::GetTransform()
	//{
	//	return Scene::GetComponent<Transform>(m_ID);
	//}

	Entity* Entity::CreateEntity()
	{
		return Scene::CreateEntity();
	}

	void Entity::InitDefaultComponents()
	{

	}
}