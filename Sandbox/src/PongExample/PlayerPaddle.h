#pragma once

#include <Merlin.h>

#include "GameState.h"

using namespace Merlin;
using namespace Merlin::Renderer;

class PlayerPaddle : public Entity
{
public:
	PlayerPaddle();

	void OnAttach() override;

	void SetupPlayer(PlayerType type, GameState* state);
	void MovePlayer(float delta);

	Material2D* mat;
	RigidBody2D* rb;
	BoxCollider2D* col;

	PlayerType type = PlayerType::Player1;
	GameState* state;

	float moveSpeed = 5.0f;
};