#pragma once

#include <Wyvern.h>

using namespace Wyvern;

struct PongBall : public NativeScriptComponent
{
	Vector2 initialForce;

	virtual void OnAttach() override;

	WV_SERIALIZE_COMPONENT(PongBall)
	WV_SERIALIZE_VARIABLE(Vector2, initialForce)
	WV_SERIALIZE_COMPONENT_END
};