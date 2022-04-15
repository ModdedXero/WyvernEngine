#include "PlayerEntity.h"

PlayerEntity::PlayerEntity()
	: m_Camera(nullptr), m_Sprite(nullptr), m_RigidBody(nullptr), m_Collider(nullptr)
{

}

void PlayerEntity::OnAttach()
{
	m_Camera = AddComponent<Camera>();
	m_Sprite = AddComponent<SpriteRenderer>();
	m_RigidBody = AddComponent<RigidBody2D>();
	m_Collider = AddComponent<BoxCollider2D>();

	GetTransform()->scale = { 0.35f, 0.35f, 1.0f };

	GetTransform()->position = {0, 0, 8};

	m_Sprite->material->shader = ResourceManager::GetShader("FlatShader");
	m_Sprite->sprite = ResourceManager::GetSprite("Player");

	m_Collider->size = GetTransform()->scale;
}

void PlayerEntity::OnCollision2D(const Collision2D& collision)
{
	DEBUG_LOG("Test1");
}

void PlayerEntity::MovePlayer(float delta)
{
	if (Input::IsKey(KeyCode::W))
	{
		GetTransform()->position.y += speed * delta;
	}

	if (Input::IsKey(KeyCode::S))
	{
		GetTransform()->position.y -= speed * delta;
	}

	if (Input::IsKey(KeyCode::A))
	{
		GetTransform()->position.x -= speed * delta;
	}

	if (Input::IsKey(KeyCode::D))
	{
		GetTransform()->position.x += speed * delta;
	}
}