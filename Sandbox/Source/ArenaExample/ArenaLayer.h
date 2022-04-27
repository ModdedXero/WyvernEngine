#pragma once

#include <Wyvern.h>

#include "PlayerEntity.h"

class ArenaLayer : public Wyvern::Layer
{
private:
	PlayerEntity* player;
public:
	ArenaLayer();
	
	void OnAttach() override;
	void OnUpdate(Wyvern::Timestep ts) override;
	void OnImGuiRender() override;
private:
	int fps;
};