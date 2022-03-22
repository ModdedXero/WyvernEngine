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
	Material2D* m_Material;
	RigidBody2D* m_RigidBody;
	BoxCollider2D* m_Collider;
};