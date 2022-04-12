#pragma once

#include <Merlin.h>

using namespace Merlin;
using namespace Merlin::Renderer;

class PlayerEntity : public Entity
{
private:
	float speed = 2.0f;
public:
	PlayerEntity();

	void OnAttach() override;
	void OnCollision2D(const Collision2D& collision) override;

	void MovePlayer(float delta);
private:
	Camera* m_Camera;
	SpriteRenderer* m_Sprite;
	RigidBody2D* m_RigidBody;
	BoxCollider2D* m_Collider;
};