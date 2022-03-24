#include "TopWall.h"

TopWall::TopWall()
	: PongWall()
{

}

void TopWall::OnAttach()
{
	PongWall::OnAttach();

	GetTransform()->position = { 0, 4, 0 };
	GetTransform()->scale = { 4.125f, 0.125f, 1 };
	col->size = { 4.125f, 0.125f };
}