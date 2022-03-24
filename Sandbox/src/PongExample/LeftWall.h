#pragma once

#include "PongWall.h"
#include "GameState.h"

using namespace Merlin;
using namespace Merlin::Renderer;

class LeftWall : public PongWall
{
public:
	LeftWall();

	void OnAttach() override;
	void OnCollision2D(const Collision2D& collision) override;

	void SetupWall(GameState* state);
private:
	GameState* state;
};