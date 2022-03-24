#include "PongLayer.h"

#include "LeftWall.h"
#include "RightWall.h"
#include "TopWall.h"
#include "BottomWall.h"

#include <imgui.h>

using namespace Merlin;
using namespace Merlin::Renderer;

PongLayer::PongLayer()
	: Layer("Arena Layer"), fps(0), state(nullptr), player1(nullptr), player2(nullptr), ball(nullptr)
{
}

void PongLayer::OnAttach()
{
	state = new GameState();

	Entity* camera = Entity::CreateEntity();
	Camera* cam = camera->AddComponent<Camera>();
	cam->offset = { 0,0,8 };
	cam->transform = camera->GetTransform();

	LeftWall* left = Scene::CreateEntity<LeftWall>();
	RightWall* right = Scene::CreateEntity<RightWall>();
	TopWall* top = Scene::CreateEntity<TopWall>();
	BottomWall* bottom = Scene::CreateEntity<BottomWall>();

	player1 = Scene::CreateEntity<PlayerPaddle>();
	player1->SetupPlayer(PlayerType::Player1, state);

	player2 = Scene::CreateEntity<PlayerPaddle>();
	player2->SetupPlayer(PlayerType::Player2, state);

	ball = Entity::CreateEntity();
	ball->GetTag()->name = "Ball";
	Material2D* matb = ball->AddComponent<Material2D>();
	matb->shader = ResourceManager::GetShader("FlatShader");
	matb->texture = ResourceManager::GetTexture("Ball");
	matb->color = { 1,1,1,1 };
	ball->GetTransform()->scale = { 0.25f, 0.25f, 1 };
	SphereCollider2D* ballCol = ball->AddComponent<SphereCollider2D>();
	ballCol->radius = 0.25f;
	RigidBody2D* ballRb = ball->AddComponent<RigidBody2D>();
	ballRb->bounce = 1.0f;
	ballRb->drag = 0;
	ballRb->force += {-300, 180};
}

void PongLayer::OnUpdate(Merlin::Timestep ts)
{
	fps = ts.GetFPS();

	player1->MovePlayer(ts.GetDeltaTime());
	player2->MovePlayer(ts.GetDeltaTime());
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