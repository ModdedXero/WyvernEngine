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

	void CheckScore();
private:
	int fps;

	GameState* state;

	PlayerPaddle* player1;
	PlayerPaddle* player2;

	Entity* ball;

	Entity* p1Score1;
	Entity* p1Score2;
	Entity* p1Score3;

	Entity* p2Score1;
	Entity* p2Score2;
	Entity* p2Score3;
};