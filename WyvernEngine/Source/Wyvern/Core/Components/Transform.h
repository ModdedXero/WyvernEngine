#pragma once

#include <Wyvern/Core/Scene/Component.h>
#include <Wyvern/Core/Math/Math.h>

namespace Wyvern
{
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

		Matrix4x4 GetTransform();
		Matrix4x4 GetGlobalTransform();

		virtual void DrawEditor() override;

		WV_SERIALIZE_COMPONENT(Transform)
		WV_SERIALIZE_VARIABLE(Vector3, position)
		WV_SERIALIZE_VARIABLE(Vector3, rotation)
		WV_SERIALIZE_VARIABLE(Vector3, scale)
		WV_SERIALIZE_COMPONENT_END
	};
}