#pragma once

#include <Merlin.h>

using namespace Merlin;

class FloorEntity : public Entity
{
public:
	Transform* transform;
	Material2D* mat;

	void OnAttach() override
	{
		transform = GetTransform();
		GetTransform()->scale = { 0.5f, 0.5f, 1.0f };
		mat = AddComponent<Material2D>();
		mat->shader = ResourceManager::GetShader("FlatShader");
		mat->color = { 0.5f, 0.3f, 0.2f, 1.0f };
	}
};

class Player : public Entity
{
public:
	Transform* transform;
	RigidBody2D* rb;
	Material2D* mat;
	Camera* cam;

	float speed = 3000.0f;

	void OnAttach() override
	{
		transform = GetTransform();
		transform->scale = { 0.35f, 0.35f, 1.0f };
		mat = AddComponent<Material2D>();
		mat->shader = ResourceManager::GetShader("FlatShader");
		mat->subTexture = ResourceManager::GetSubTexture("Player");
		mat->color = { 0.2f, 0.3f, 0.8f, 1.0f };
		rb = AddComponent<RigidBody2D>();
		AddComponent<BoxCollider2D>()->size = transform->scale - Vector2(0.025f, 0.025f);
		Camera* cam = AddComponent<Camera>();
		cam->transform = GetTransform();
		cam->offset = { 0, 0, 8 };
	}

	void MovePlayer(float delta)
	{
		if (Input::IsKey(KeyCode::W))
		{
			rb->force += Vector2(0, 1) * speed * delta;
		}

		if (Input::IsKey(KeyCode::S))
		{
			rb->force += Vector2(0, -1) * speed * delta;
		}

		if (Input::IsKey(KeyCode::A))
		{
			rb->force += Vector2(-1, 0) * speed * delta;
		}

		if (Input::IsKey(KeyCode::D))
		{
			rb->force += Vector2(1, 0) * speed * delta;
		}
	}
};

class RelicLayer : public Layer
{
public:
	Player* player;

	void OnAttach() override
	{
		Entity* test = Entity::CreateEntity();

		int TileMap[10][10] =
		{
			{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
			{1, 1, 2, 2, 2, 2, 2, 2, 2, 1},
			{1, 1, 2, 1, 1, 1, 1, 1, 2, 1},
			{1, 1, 2, 1, 1, 1, 1, 1, 2, 1},
			{1, 1, 2, 1, 1, 1, 1, 1, 2, 1},
			{1, 1, 2, 1, 1, 1, 1, 1, 2, 1},
			{1, 1, 2, 2, 2, 1, 2, 2, 2, 1},
			{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
			{1, 3, 1, 1, 1, 1, 1, 1, 1, 1},
			{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
		};

		for (int row = 10; row >= 0; row--)
		{
			for (int col = 0; col < 10; col++)
			{
				if (TileMap[col][row] == 3)
				{
					FloorEntity* tile = Scene::CreateEntity<FloorEntity>();
					tile->GetTransform()->position += Vector2(row + 5.0f, -col + 5.0f);
					tile->mat->subTexture = ResourceManager::GetSubTexture("Floor");
				}
				else if (TileMap[col][row] == 4)
				{
					FloorEntity* tile = Scene::CreateEntity<FloorEntity>();
					tile->GetTransform()->position += Vector2(row + 5.0f, -col + 5.0f);
					tile->mat->subTexture = ResourceManager::GetSubTexture("Wall");
					RigidBody2D* rb = tile->AddComponent<RigidBody2D>();
					rb->bodyType = RigidBody2D::PhysicsBody::Static;
					rb->mass = 0.0f;
					tile->AddComponent<BoxCollider2D>()->size = tile->GetTransform()->scale;
				}
				else
					ML_LOG_INFO(TileMap[row][col], " || ", row, " || ", col);
			}
		}

		player = Scene::CreateEntity<Player>();
	}

	void OnUpdate(Timestep ts) override
	{
		player->MovePlayer(ts.GetDeltaTime());
	}
};