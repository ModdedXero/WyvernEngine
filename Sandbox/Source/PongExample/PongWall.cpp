#include "PongWall.h"

PongWall::PongWall()
	: mat(nullptr), rb(nullptr), col(nullptr)
{

}

void PongWall::OnAttach()
{
	mat = AddComponent<SpriteRenderer>();
	mat->material = AssetManager::GetMaterial("StandardMaterial");
	mat->color = { 1,1,1,1 };

	rb = AddComponent<RigidBody2D>();
	rb->bodyType = RigidBody2D::PhysicsBody::Static;
	rb->bounce = 1.0f;
	rb->mass = 0;

	col = AddComponent<BoxCollider2D>();
}