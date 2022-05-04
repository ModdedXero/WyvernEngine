#include "LeftWall.h"

LeftWall::LeftWall()
	: PongWall()
{

}

void LeftWall::OnAttach()
{
	PongWall::OnAttach();
	
	GetTransform()->position = { -4, 0, 0 };
	GetTransform()->scale = { 0.125f, 4, 1 };
	col->size = { 0.125f, 4 };
}

void LeftWall::OnCollision2D(const Collision2D& collision)
{
	if (collision.entB->GetTag()->name == "Ball")
	{
		state->player1Lives--;
	}
}

void LeftWall::SetupWall(GameState* state)
{
	this->state = state;
}