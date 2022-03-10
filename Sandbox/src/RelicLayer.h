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
		GetTransform()->scale = { 0.25f, 0.25f, 1.0f };
		mat = AddComponent<Material2D>();
		mat->shader = ResourceManager::GetShader("FlatShader").ID;
		mat->subTexture = "WallUpperLeft";
		Camera* cam = AddComponent<Camera>();
	}
};

class RelicLayer : public Layer
{
public:
	void OnAttach() override
	{
		Entity* test = Entity::CreateEntity();
		Camera* cam = test->AddComponent<Camera>();
		cam->transform = test->GetTransform();
		cam->offset = { 0, 0, 8 };

		for (float x = -5.0f; x < 5.0f; x += 0.75f)
		{
			for (float y = -5.0f; y < 5.0f; y += 0.75f)
			{
				FloorEntity* ent = Scene::CreateEntity<FloorEntity>();
				ent->transform->position += {x, y};
				ML_LOG_INFO(ent->transform->position);
			}
		}
	}

	void OnUpdate(Timestep ts) override
	{

	}
};