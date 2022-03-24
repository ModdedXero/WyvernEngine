#pragma once

#include <Merlin.h>

using namespace Merlin;
using namespace Merlin::Renderer;

class PongWall : public Merlin::Entity
{
public:
	PongWall();

	void OnAttach() override;

	Material2D* mat;
	RigidBody2D* rb;
	BoxCollider2D* col;
};