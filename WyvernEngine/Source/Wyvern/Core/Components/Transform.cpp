#include "wvpch.h"
#include "Transform.h"

#include <Wyvern/Core/Scene/Entity.h>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

namespace Wyvern
{
	Vector3 Transform::GlobalPosition()
	{
		if (Scene::IsEntityValid(GetEntity().GetScene(), GetEntity().GetParent()))
		{
			return Scene::GetComponent<Transform>(Scene::GetEntity(GetEntity().GetScene(), GetEntity().GetParent()))->GlobalPosition() + position;
		}

		return position;
	}

	Vector3 Transform::GlobalRotation()
	{
		if (Scene::IsEntityValid(GetEntity().GetScene(), GetEntity().GetParent()))
		{
			return Scene::GetComponent<Transform>(Scene::GetEntity(GetEntity().GetScene(), GetEntity().GetParent()))->GlobalRotation() + rotation;
		}

		return rotation;
	}

	Vector3 Transform::GlobalScale()
	{
		if (Scene::IsEntityValid(GetEntity().GetScene(), GetEntity().GetParent()))
		{
			return Scene::GetComponent<Transform>(Scene::GetEntity(GetEntity().GetScene(), GetEntity().GetParent()))->GlobalScale() * scale;
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

	static glm::quat GetOrientation(const Vector3& rotation)
	{
		return glm::quat(glm::radians(glm::vec3(-rotation.x, rotation.y, 0.0f)));
	}

	Vector3 Transform::Forward()
	{
		return (glm::vec3)glm::rotate(GetOrientation(rotation), glm::vec3(0.0f, 0.0f, -1.0f));
	}

	Vector3 Transform::Back()
	{
		return (glm::vec3)glm::rotate(GetOrientation(rotation), glm::vec3(0.0f, 0.0f, 1.0f));
	}

	Vector3 Transform::Right()
	{
		return (glm::vec3)glm::rotate(GetOrientation(rotation), glm::vec3(1.0f, 0.0f, 0.0f));
	}

	Vector3 Transform::Left()
	{
		return (glm::vec3)glm::rotate(GetOrientation(rotation), glm::vec3(-1.0f, 0.0f, 0.0f));
	}

	Vector3 Transform::Up()
	{
		return (glm::vec3)glm::rotate(GetOrientation(rotation), glm::vec3(0.0f, 1.0f, 0.0f));
	}
	Vector3 Transform::Down()
	{
		return (glm::vec3)glm::rotate(GetOrientation(rotation), glm::vec3(0.0f, -1.0f, 0.0f));
	}

	Matrix4x4 Transform::GetTransform(const Vector3& pos, const Vector3& rot, const Vector3& scale)
	{
		Matrix4x4 trans = Matrix4x4::Translate(pos)
			* Matrix4x4::Rotate(rot)
			* Matrix4x4::Scale(scale);

		return trans;
	}
}