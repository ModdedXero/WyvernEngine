#include "PongLayer.h"

#include <imgui.h>

using namespace Merlin;

PongLayer::PongLayer()
	: Layer("Arena Layer"), fps(0)
{
}

void PongLayer::OnAttach()
{

}

void PongLayer::OnUpdate(Merlin::Timestep ts)
{
	fps = ts.GetFPS();
}

void PongLayer::OnImGuiRender()
{
	ImGui::Begin("Engine Info");

	std::string fpsText("FPS: ");
	fpsText.append(std::to_string(fps).c_str());
	ImGui::Text(fpsText.c_str());

	std::string entText("Entity Count: ");
	entText.append(std::to_string(Scene::GetEntityCount()).c_str());
	ImGui::Text(entText.c_str());

	ImGui::End();
}