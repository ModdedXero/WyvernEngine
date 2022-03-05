#pragma once

#include <Merlin/Core/Math/Vector.h>

namespace Merlin
{
	struct Transform
	{
		Vector3 position;
		Vector3 rotation;
		Vector3 scale = Vector3(1, 1, 1);
	};
}