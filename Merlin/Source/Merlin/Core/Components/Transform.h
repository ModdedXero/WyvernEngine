#pragma once

#include <Merlin/Core/Scene/Component.h>

#include <Merlin/Core/Math/Vector.h>

namespace Merlin
{
	class Entity;

	struct Transform : public Component
	{
		Transform() {}
		~Transform() {}

		Vector3 position;
		Vector3 rotation;
		Vector3 scale = Vector3(1, 1, 1);

		Vector3 GlobalPosition();
		Vector3 GlobalRotation();
		Vector3 GlobalScale();
	};
}