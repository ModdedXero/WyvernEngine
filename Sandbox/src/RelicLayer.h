#pragma once

#include <Merlin.h>

using namespace Merlin;

class RelicLayer : public Layer
{
public:
	Entity* testEntity;

	void OnAttach() override
	{
		testEntity = Entity::CreateEntity();
		Material2D* testMat = testEntity->AddComponent<Material2D>();
		testMat->shader = ResourceManager::GetShader("FlatShader").ID;
		testMat->subTexture = &ResourceManager::GetSubTexture("WallUpperLeft");
		Camera* cam = testEntity->AddComponent<Camera>();
		cam->offset = { 0, 0, 8 };
	}

	void OnUpdate(Timestep ts) override
	{

	}
};