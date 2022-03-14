#include "PlayerEntity.h"

PlayerEntity::PlayerEntity()
	: m_Camera(nullptr), m_Material(nullptr), m_RigidBody(nullptr), m_Collider(nullptr)
{

}

void PlayerEntity::OnAttach()
{
	m_Camera = AddComponent<Camera>();
	m_Material = AddComponent<Material2D>();
	m_RigidBody = AddComponent<RigidBody2D>();
	m_Collider = AddComponent<BoxCollider2D>();

	GetTransform()->scale = { 0.35f, 0.35f, 1.0f };

	m_Camera->transform = GetTransform();
	m_Camera->offset = { 0, 0, 8 };

	m_Material->shader = ResourceManager::GetShader("FlatShader");
	m_Material->subTexture = ResourceManager::GetSubTexture("Player");

	m_Collider->size = GetTransform()->scale;
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