#pragma once

#include <Merlin.h>

#include "GameState.h"
#include "PlayerPaddle.h"

class PongLayer : public Merlin::Layer
{
public:
	PongLayer();

	void OnAttach() override;
	void OnUpdate(Merlin::Timestep ts) override;
	void OnImGuiRender() override;
private:
	int fps;

	GameState* state;

	PlayerPaddle* player1;
	PlayerPaddle* player2;

	Entity* ball;
};