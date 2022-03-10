#pragma once

#include "Merlin.h"

#include <memory>

using namespace Merlin;
using namespace Merlin::Events;
using namespace Merlin::Renderer;

class PlayerEntity : public Entity
{
public:
	Transform* transform;
	RigidBody2D* rb;
	BoxCollider2D* collider;
	Material2D* mat;
	Camera* cam;

	float speed = 35.0f;

	void OnAttach() override
	{
		transform = GetTransform();
		transform->scale = { 0.25f, 0.25f, 1.0f };
		transform->position = { -4.0f, 0, 0 };
		rb = AddComponent<RigidBody2D>();
		rb->bounce = 0.7f;
		rb->mass = 2.0f;
		collider = AddComponent<BoxCollider2D>();
		collider->size = transform->scale;
		mat = AddComponent<Material2D>();
		mat->shader = ResourceManager::GetShader("FlatShader").ID;
		mat->color = { 0.3f, 0.6f, 0.9f, 1.0f };

		cam = AddComponent<Camera>();
		cam->transform = transform;
		cam->offset = Vector3(0, 0, -8.0f);
	}

	void OnCollision2D(const Collision2D& collision) override
	{

	}

	void MovePlayer(float delta)
	{
		if (Input::IsKey(KeyCode::W))
		{
			rb->force += Vector2(0, 1) * speed;
		}

		if (Input::IsKey(KeyCode::S))
		{
			rb->force += Vector2(0, -1) * speed;
		}

		if (Input::IsKey(KeyCode::A))
		{
			rb->force += Vector2(-1, 0) * speed;
		}

		if (Input::IsKey(KeyCode::D))
		{
			rb->force += Vector2(1, 0) * speed;
		}
	}
};

class BulletEntity : public Entity
{
public:
	Transform* transform;
	RigidBody2D* rb;
	BoxCollider2D* collider;
	Material2D* mat;

	void OnAttach() override
	{
		transform = GetTransform();
		transform->scale = { 0.15f, 0.15f, 1.0f };
		transform->position = { -4.0f, 0, 0 };
		rb = AddComponent<RigidBody2D>();
		rb->friction = 0.0f;
		rb->bounce = 0.0f;
		rb->bodyType = RigidBody2D::PhysicsBody::Kinematic;
		collider = AddComponent<BoxCollider2D>();
		collider->size = transform->scale;
		mat = AddComponent<Material2D>();
		mat->shader = ResourceManager::GetShader("FlatShader").ID;
		mat->color = { 0.3f, 0.2f, 0.4f, 1.0f };
	}

	void OnCollision2D(const Collision2D& collision) override
	{
		Scene::DestroyEntity(m_ID);
	}
};

class ObstacleEntity : public Entity
{
public:
	Transform* transform;
	RigidBody2D* rb;
	BoxCollider2D* collider;
	Material2D* mat;

	float speed = 20.0f;

	void OnAttach() override
	{
		transform = GetTransform();
		transform->scale = { 0.25f, 0.25f, 1.0f };

		rb = AddComponent<RigidBody2D>();
		collider = AddComponent<BoxCollider2D>();
		collider->size = transform->scale;
		mat = AddComponent<Material2D>();
		mat->shader = ResourceManager::GetShader("FlatShader").ID;
		mat->color = { 0.3f, 0.6f, 0.2f, 1.0f };
	}
};

class ExampleLayer : public Layer
{
	PlayerEntity* player;
	Entity* gameFloor;

	ObstacleEntity* obs1;
	ObstacleEntity* obs2;
	ObstacleEntity* obs3;
	ObstacleEntity* obs4;

	void OnAttach() override
	{
		// Player
		player = Scene::CreateEntity<PlayerEntity>();

		// Floor
		gameFloor = Entity::CreateEntity();
		Transform* floorTs = gameFloor->GetTransform();
		floorTs->scale = { 6.0f, 0.5f, 1.0f };
		floorTs->position = { 0, -3.0f, 0 };
		RigidBody2D* rb = gameFloor->AddComponent<RigidBody2D>();
		rb->bodyType = RigidBody2D::PhysicsBody::Static;
		rb->mass = 0.0f;
		BoxCollider2D* box2 = gameFloor->AddComponent<BoxCollider2D>();
		box2->size = floorTs->scale;
		Material2D* floorMat = gameFloor->AddComponent<Material2D>();
		floorMat->shader = ResourceManager::GetShader("FlatShader").ID;
		floorMat->color = { 0.7f, 0.3f, 0.4f, 1.0f };

		// Boxes
		obs1 = Scene::CreateEntity<ObstacleEntity>();
		obs1->transform->position = { 0.0f, 0.0f, 0 };
		obs1->rb->bounce = 0.4f;

		obs2 = Scene::CreateEntity<ObstacleEntity>();
		obs2->transform->position = { 1.0f, 0.0f, 0 };
		obs2->rb->bounce = 0.5f;

		obs3 = Scene::CreateEntity<ObstacleEntity>();
		obs3->transform->position = { 1.0f, 0.0f, 0 };
		obs3->rb->bounce = 0.6f;

		obs4 = Scene::CreateEntity<ObstacleEntity>();
		obs4->transform->position = { 3.0f, 0.0f, 0 };
		obs4->rb->bounce = 0.7f;
	}

	void OnUpdate(Timestep ts) override
	{
		player->MovePlayer(ts.GetDeltaTime());
		if (Input::IsKey(KeyCode::U))
		{
			BulletEntity* bullet = Scene::CreateEntity<BulletEntity>();
			bullet->rb->velocity = Vector2(1, 0) * 40.0f;
		}
	}
};
