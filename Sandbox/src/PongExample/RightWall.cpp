#include "RightWall.h"

RightWall::RightWall()
	: PongWall()
{

}

void RightWall::OnAttach()
{
	PongWall::OnAttach();

	GetTransform()->position = { 4, 0, 0 };
	GetTransform()->scale = { 0.125f, 4, 1 };
	col->size = { 0.125f, 4 };
}

void RightWall::OnCollision2D(const Collision2D& collision)
{
	if (collision.entityB->GetTag()->name == "Ball")
	{
		state->player2Lives--;
	}
}

void RightWall::SetupWall(GameState* state)
{
	this->state = state;
}