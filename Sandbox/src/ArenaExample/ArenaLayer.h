#pragma once

#include <Merlin.h>

#include "PlayerEntity.h"

class ArenaLayer : public Merlin::Layer
{
private:
	PlayerEntity* player;
public:
	ArenaLayer();
	
	void OnAttach() override;
	void OnUpdate(Merlin::Timestep ts) override;
	void OnImGuiRender() override;
private:
	int fps;
};