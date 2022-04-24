#pragma once

#include "PongWall.h"

using namespace Merlin;
using namespace Merlin::Renderer;

class TopWall : public PongWall
{
public:
	TopWall();

	void OnAttach() override;
};