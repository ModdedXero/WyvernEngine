#include "mlpch.h"
#include "Transform.h"

#include <Merlin/Core/Scene/Entity.h>
#include <Merlin/Core/Scene/SerializeHelper.h>

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

	void Transform::Serialize(YAML::Emitter& out)
	{
		out << YAML::Key << "Transform";
		out << YAML::BeginMap;

		out << YAML::Key << "position" << YAML::Value << position;
		out << YAML::Key << "rotation" << YAML::Value << rotation;
		out << YAML::Key << "scale" << YAML::Value << scale;

		out << YAML::EndMap;
	}

	void Transform::Deserialize(Entity* ent, YAML::Node& data)
	{
		Transform* transform = ent->GetTransform();

		transform->position = data["position"].as<Vector3>();
		transform->rotation = data["rotation"].as<Vector3>();
		transform->scale = data["scale"].as<Vector3>();
	}
}