#pragma once

#include "PongWall.h"

using namespace Merlin;
using namespace Merlin::Renderer;

class BottomWall : public PongWall
{
public:
	BottomWall();

	void OnAttach() override;
};