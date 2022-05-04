#pragma once

#include "Wyvern.h"

using namespace Wyvern;

struct TestMovement : public NativeScriptComponent
{
	virtual void OnUpdate() override;

	WV_SERIALIZE_COMPONENT(TestMovement)
	WV_SERIALIZE_COMPONENT_END
};