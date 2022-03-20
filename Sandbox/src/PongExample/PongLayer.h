#pragma once

#include <Merlin.h>

class PongLayer : public Merlin::Layer
{
public:
	PongLayer();

	void OnAttach() override;
	void OnUpdate(Merlin::Timestep ts) override;
	void OnImGuiRender() override;
private:
	int fps;
};