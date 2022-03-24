#pragma once

#include "Component.h"

#include <Merlin/Core/Math/Vector.h>

namespace Merlin
{
	struct Transform : public Component
	{
		Transform() {}
		~Transform() {}

		Vector3 position;
		Vector3 rotation;
		Vector3 scale = Vector3(1, 1, 1);
	};
}