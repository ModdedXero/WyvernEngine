#pragma once

#include <Wyvern.h>

#include "GameState.h"

using namespace Wyvern;
using namespace Wyvern::Renderer;

class PlayerPaddle : public Entity
{
public:
	PlayerPaddle();

	void OnAttach() override;

	void SetupPlayer(PlayerType type, GameState* state);
	void MovePlayer(float delta);

	SpriteRenderer* mat;
	RigidBody2D* rb;
	BoxCollider2D* col;

	PlayerType type = PlayerType::Player1;
	GameState* state;

	float moveSpeed = 5.0f;
};