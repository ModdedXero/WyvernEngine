#pragma once

#include "PongWall.h"

using namespace Wyvern;
using namespace Wyvern::Renderer;

class BottomWall : public PongWall
{
public:
	BottomWall();

	void OnAttach() override;
};