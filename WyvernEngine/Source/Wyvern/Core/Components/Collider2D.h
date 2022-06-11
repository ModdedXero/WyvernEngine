#pragma once

#include <Wyvern/Core/Math/Vector.h>
#include <Wyvern/Core/Scene/NativeScriptComponent.h>

namespace Wyvern
{
	struct BoxCollider2D : public NativeScriptComponent<BoxCollider2D, Vector2>
	{
		Vector2 size = Vector2(0, 0);

		virtual void DrawEditor() override;
	};

	struct SphereCollider2D : public NativeScriptComponent<BoxCollider2D, float>
	{
		float radius = 0.0f;

		virtual void DrawEditor() override;
	};
}