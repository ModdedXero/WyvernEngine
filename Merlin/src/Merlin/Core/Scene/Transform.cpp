#include "mlpch.h"
#include "Transform.h"

#include "Entity.h"

namespace Merlin
{
	Vector3 Transform::GlobalPosition()
	{
		if (GetEntity()->GetParent())
		{
			return GetEntity()->GetParent()->GetTransform()->GlobalPosition() + position;
		}

		return position;
	}

	Vector3 Transform::GlobalRotation()
	{
		if (GetEntity()->GetParent())
		{
			return GetEntity()->GetParent()->GetTransform()->GlobalRotation() + rotation;
		}

		return rotation;
	}

	Vector3 Transform::GlobalScale()
	{
		if (GetEntity()->GetParent())
		{
			return GetEntity()->GetParent()->GetTransform()->GlobalScale() * scale;
		}

		return scale;
	}
}