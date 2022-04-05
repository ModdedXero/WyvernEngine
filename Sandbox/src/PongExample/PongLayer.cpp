#include "PongLayer.h"

#include "LeftWall.h"
#include "RightWall.h"
#include "TopWall.h"
#include "BottomWall.h"

#include <imgui.h>

using namespace Merlin;
using namespace Merlin::Renderer;
using namespace Merlin::UI;

PongLayer::PongLayer()
	: Layer("Arena Layer"), fps(0), state(nullptr), player1(nullptr), player2(nullptr), ball(nullptr)
{
}

void TestHover()
{
	DEBUG_LOG("Hover Bro");
}

void PongLayer::OnAttach()
{
	state = new GameState();

	Entity* camera = Entity::CreateEntity();
	Camera* cam = camera->AddComponent<Camera>();
	cam->offset = { 0,0,8 };

	LeftWall* left = Scene::CreateEntity<LeftWall>();
	left->SetupWall(state);
	RightWall* right = Scene::CreateEntity<RightWall>();
	right->SetupWall(state);
	TopWall* top = Scene::CreateEntity<TopWall>();
	BottomWall* bottom = Scene::CreateEntity<BottomWall>();
	Button* button = bottom->AddComponent<Button>();
	button->OnClick = TestHover;

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
	ball->GetTransform()->scale = { 0.15f, 0.15f, 1 };
	SphereCollider2D* ballCol = ball->AddComponent<SphereCollider2D>();
	ballCol->radius = 0.15f;
	RigidBody2D* ballRb = ball->AddComponent<RigidBody2D>();
	ballRb->bounce = 1.0f;
	ballRb->drag = 0;
	ballRb->force += {-300, 180};

	p1Score1 = Entity::CreateEntity();
	Material2D* p1sMat = p1Score1->AddComponent<Material2D>();
	p1sMat->shader = ResourceManager::GetShader("FlatShader");
	p1sMat->color = { 0.5f,1,0.7f,1 };
	p1Score1->GetTransform()->position = { -4.5f, 3.3f, 1 };
	p1Score1->GetTransform()->scale = { 0.05f, 0.3f, 1 };

	p1Score2 = Entity::CreateEntity();
	Material2D* p2sMat = p1Score2->AddComponent<Material2D>();
	p2sMat->shader = ResourceManager::GetShader("FlatShader");
	p2sMat->color = { 0.5f,1,0.7f,1 };
	p1Score2->GetTransform()->position = { -4.7f, 3.3f, 1 };
	p1Score2->GetTransform()->scale = { 0.05f, 0.3f, 1 };

	p1Score3 = Entity::CreateEntity();
	Material2D* p3sMat = p1Score3->AddComponent<Material2D>();
	p3sMat->shader = ResourceManager::GetShader("FlatShader");
	p3sMat->color = { 0.5f,1,0.7f,1 };
	p1Score3->GetTransform()->position = { -4.9f, 3.3f, 1 };
	p1Score3->GetTransform()->scale = { 0.05f, 0.3f, 1 };

	p2Score1 = Entity::CreateEntity();
	Material2D* p4sMat = p2Score1->AddComponent<Material2D>();
	p4sMat->shader = ResourceManager::GetShader("FlatShader");
	p4sMat->color = { 0.5f,1,0.7f,1 };
	p2Score1->GetTransform()->position = { 4.5f, 3.3f, 1 };
	p2Score1->GetTransform()->scale = { 0.05f, 0.3f, 1 };

	p2Score2 = Entity::CreateEntity();
	Material2D* p5sMat = p2Score2->AddComponent<Material2D>();
	p5sMat->shader = ResourceManager::GetShader("FlatShader");
	p5sMat->color = { 0.5f,1,0.7f,1 };
	p2Score2->GetTransform()->position = { 4.7f, 3.3f, 1 };
	p2Score2->GetTransform()->scale = { 0.05f, 0.3f, 1 };

	p2Score3 = Entity::CreateEntity();
	Material2D* p6sMat = p2Score3->AddComponent<Material2D>();
	p6sMat->shader = ResourceManager::GetShader("FlatShader");
	p6sMat->color = { 0.5f,1,0.7f,1 };
	p2Score3->GetTransform()->position = { 4.9f, 3.3f, 1 };
	p2Score3->GetTransform()->scale = { 0.05f, 0.3f, 1 };
}

void PongLayer::OnUpdate(Merlin::Timestep ts)
{
	fps = ts.GetFPS();

	player1->MovePlayer(ts.GetDeltaTime());
	player2->MovePlayer(ts.GetDeltaTime());

	Renderer2D::DrawText({ 0,0 }, { 0.01f, 0.01f }, "I really love Pong!");

	CheckScore();
}

void PongLayer::CheckScore()
{
	if (state->player1Lives == 2)
	{
		Scene::DestroyEntity(p1Score1->GetID());
	}
	if (state->player1Lives == 1)
	{
		Scene::DestroyEntity(p1Score2->GetID());
	}
	if (state->player1Lives == 0)
	{
		Scene::DestroyEntity(p1Score3->GetID());
		Scene::DestroyEntity(ball->GetID());
	}

	if (state->player2Lives == 2)
	{
		Scene::DestroyEntity(p2Score3->GetID());
	}
	if (state->player2Lives == 1)
	{
		Scene::DestroyEntity(p2Score2->GetID());
	}
	if (state->player2Lives == 0)
	{
		Scene::DestroyEntity(p2Score1->GetID());
		Scene::DestroyEntity(ball->GetID());
	}
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

	std::string mouseText("Mouse Position: ");
	mouseText.append(std::to_string(Input::MousePosition().x).c_str());
	mouseText.append(", ");
	mouseText.append(std::to_string(Input::MousePosition().y).c_str());
	ImGui::Text(mouseText.c_str());

	ImGui::End();
}
