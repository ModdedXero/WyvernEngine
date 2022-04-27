#pragma once

#include <Wyvern.h>

using namespace Wyvern;
using namespace Wyvern::Renderer;

class PongWall : public Wyvern::Entity
{
public:
	PongWall();

	void OnAttach() override;

	SpriteRenderer* mat;
	RigidBody2D* rb;
	BoxCollider2D* col;
};