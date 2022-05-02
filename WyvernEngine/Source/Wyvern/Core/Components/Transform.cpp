#include "wvpch.h"
#include "Transform.h"

#include <Wyvern/Core/Scene/Entity.h>

namespace Wyvern
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

	Matrix4x4 Transform::GetTransform()
	{
		Matrix4x4 trans = Matrix4x4::Translate(position)
			* Matrix4x4::Rotate(rotation)
			* Matrix4x4::Scale(scale);

		return trans;
	}

	Matrix4x4 Transform::GetGlobalTransform()
	{
		if (GetEntity()->GetParent())
		{
			Matrix4x4 trans = Matrix4x4::Translate(GetEntity()->GetParent()->GetTransform()->GlobalPosition() + position)
				* Matrix4x4::Rotate(GetEntity()->GetParent()->GetTransform()->GlobalRotation() + rotation)
				* Matrix4x4::Scale(GetEntity()->GetParent()->GetTransform()->GlobalScale() * scale);
			return trans;
		}

		return GetTransform();
	}
}