#include "PlayerPaddle.h"

PlayerPaddle::PlayerPaddle()
	: mat(nullptr), rb(nullptr), col(nullptr), state(nullptr)
{

}

void PlayerPaddle::OnAttach()
{
	mat = AddComponent<Material2D>();
	mat->shader = ResourceManager::GetShader("FlatShader");
	mat->color = { 1,1,1,1 };

	GetTransform()->scale = { 0.125f, 0.5f, 1 };
	GetTag()->name = "Player";

	col = AddComponent<BoxCollider2D>();
	col->size = { 0.125f, 0.5f };

	rb = AddComponent<RigidBody2D>();
	rb->bodyType = RigidBody2D::PhysicsBody::Dynamic;
	rb->bounce = 1.0f;
	rb->mass = 100000000;
}

void PlayerPaddle::SetupPlayer(PlayerType type, GameState* state)
{
	this->type = type;
	this->state = state;

	if (type == PlayerType::Player1)
	{
		GetTransform()->position = { -3.5f, 0, 0 };
	}
	else
	{
		GetTransform()->position = { 3.5f, 0, 0 };
	}
}

void PlayerPaddle::MovePlayer(float delta)
{
	// DEBUG_LOG(GetTransform()->position);

	if (type == PlayerType::Player1)
	{
		if (Input::IsKey(KeyCode::W))
		{
			GetTransform()->position.y += moveSpeed * delta;
		}

		if (Input::IsKey(KeyCode::S))
		{
			GetTransform()->position.y -= moveSpeed * delta;
		}
	}
	else
	{
		if (Input::IsKey(KeyCode::Up))
		{
			GetTransform()->position.y += moveSpeed * delta;
		}

		if (Input::IsKey(KeyCode::Down))
		{
			GetTransform()->position.y -= moveSpeed * delta;
		}
	}
}