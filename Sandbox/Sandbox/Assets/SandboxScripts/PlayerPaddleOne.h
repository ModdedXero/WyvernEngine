#pragma once

#include "Wyvern.h"

using namespace Wyvern;

struct PlayerPaddleOne : public NativeScriptComponent
{
	virtual void OnUpdate() override;

	float paddleSpeed = 1.0f;
	int altControls = 0;

	WV_SERIALIZE_COMPONENT(PlayerPaddleOne)
	WV_SERIALIZE_VARIABLE(float, paddleSpeed)
	WV_SERIALIZE_VARIABLE(int, altControls)
	WV_SERIALIZE_COMPONENT_END
};