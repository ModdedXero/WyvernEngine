#pragma once

#include <Merlin/Core/Math/Vector.h>

namespace Merlin
{
	struct Transform
	{
		Vector3 position;
		Vector3 rotation;
		Vector3 scale = Vector3(1, 1, 1);
		const Vector3 GetNormalPosition() { return Vector3(position.x - scale.x / 2, position.y - scale.y / 2, position.z - scale.z / 2); }
	};
}