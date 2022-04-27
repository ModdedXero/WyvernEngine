#pragma once

#include "PongWall.h"
#include "GameState.h"

using namespace Wyvern;
using namespace Wyvern::Renderer;

class RightWall : public PongWall
{
public:
	RightWall();

	void OnAttach() override;
	void OnCollision2D(const Collision2D& collision) override;

	void SetupWall(GameState* state);
private:
	GameState* state;
};