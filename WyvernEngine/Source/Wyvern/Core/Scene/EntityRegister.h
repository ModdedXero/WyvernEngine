#pragma once

#include <Wyvern/Core/UUID.h>
#include "Scene.h"
#include "EntityConstants.h"

#include <Wyvern/Core/Base.h>

#include <bitset>

namespace Wyvern
{
	struct EntityRegister
	{
		EntityRegister(bool isValid = true)
		{
			if (isValid) return;

			UniqueID = 0;
			SceneID = Scene::CreateSceneID(SceneIndex(-1), 0);
			SceneRef = nullptr;
		}

		UUID UniqueID;
		SceneID SceneID;
		Ref<Scene> SceneRef;
		ComponentMask Components;

		UUID Parent;
		std::vector<UUID> Children;
	};
}