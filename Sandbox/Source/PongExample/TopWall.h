#pragma once

#include "PongWall.h"

using namespace Wyvern;
using namespace Wyvern::Renderer;

class TopWall : public PongWall
{
public:
	TopWall();

	void OnAttach() override;
};