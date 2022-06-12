#pragma once

#include <Wyvern/Core/Scene/Component.h>
#include <Wyvern/Core/Math/Math.h>

namespace Wyvern
{
	struct Transform : public Component<Transform, Vector3, Vector3, Vector3>
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

		Vector3 Forward();
		Vector3 Back();
		Vector3 Right();
		Vector3 Left();
		Vector3 Up();
		Vector3 Down();

		static Matrix4x4 GetTransform(const Vector3& pos, const Vector3& rot, const Vector3& scale);

		virtual void DrawEditor() override;
	};
}