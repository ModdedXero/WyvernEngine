#include "PongLayer.h"

#include "PongWall.h"

#include <imgui.h>

using namespace Merlin;
using namespace Merlin::Renderer;

PongLayer::PongLayer()
	: Layer("Arena Layer"), fps(0)
{
}

void PongLayer::OnAttach()
{
	Entity* camera = Entity::CreateEntity();
	Camera* cam = camera->AddComponent<Camera>();
	cam->offset = { 0,0,8 };
	cam->transform = camera->GetTransform();

	Entity* wall1 = Entity::CreateEntity();
	Material2D* mat1 = wall1->AddComponent<Material2D>();
	mat1->shader = ResourceManager::GetShader("FlatShader");
	mat1->color = { 1,0,1,1 };
	wall1->GetTransform()->position = { 4, 0, 0 };
	wall1->GetTransform()->scale = { 0.125f, 4, 1 };

	Entity* wall2 = Entity::CreateEntity();
	Material2D* mat2 = wall2->AddComponent<Material2D>();
	mat2->shader = ResourceManager::GetShader("FlatShader");
	mat2->color = { 1,1,1,1 };
	wall2->GetTransform()->position = { -4, 0, 0 };
	wall2->GetTransform()->scale = { 0.125f, 4, 1 };

	Entity* wall3 = Entity::CreateEntity();
	Material2D* mat3 = wall3->AddComponent<Material2D>();
	mat3->shader = ResourceManager::GetShader("FlatShader");
	mat3->color = { 1,1,1,1 };
	wall3->GetTransform()->position = { 0, 4, 0 };
	wall3->GetTransform()->scale = { 4.125f, 0.125f, 1 };

	Entity* wall4 = Entity::CreateEntity();
	Material2D* mat4 = wall4->AddComponent<Material2D>();
	mat4->shader = ResourceManager::GetShader("FlatShader");
	mat4->color = { 1,1,1,1 };
	wall4->GetTransform()->position = { 0, -4, 0 };
	wall4->GetTransform()->scale = { 4.125f, 0.125f, 1 };

	BoxCollider2D* col4 = wall1->AddComponent<BoxCollider2D>();
	col4->size = wall1->GetTransform()->scale;
	RigidBody2D* rb4 = wall1->AddComponent<RigidBody2D>();
	rb4->bodyType = RigidBody2D::PhysicsBody::Static;
	rb4->bounce = 1.0f;
	rb4->mass = 0;

	Entity* player1 = Entity::CreateEntity();
	Material2D* matp1 = player1->AddComponent<Material2D>();
	matp1->shader = ResourceManager::GetShader("FlatShader");
	matp1->color = { 1,1,1,1 };
	player1->GetTransform()->position = { 3.5f, 0, 0 };
	player1->GetTransform()->scale = { 0.125f, 0.5f, 1 };

	Entity* player2 = Entity::CreateEntity();
	Material2D* matp2 = player2->AddComponent<Material2D>();
	matp2->shader = ResourceManager::GetShader("FlatShader");
	matp2->color = { 1,1,1,1 };
	player2->GetTransform()->position = { -3.5f, 0, 0 };
	player2->GetTransform()->scale = { 0.125f, 2.0f, 1 };
	BoxCollider2D* player2Col = player2->AddComponent<BoxCollider2D>();
	player2Col->size = player2->GetTransform()->scale;
	RigidBody2D* player2Rb = player2->AddComponent<RigidBody2D>();
	player2Rb->bodyType = RigidBody2D::PhysicsBody::Static;
	player2Rb->bounce = 0.8f;
	player2Rb->mass = 0;

	Entity* ball = Entity::CreateEntity();
	Material2D* matb = ball->AddComponent<Material2D>();
	matb->shader = ResourceManager::GetShader("FlatShader");
	matb->texture = ResourceManager::GetTexture("Ball");
	matb->color = { 1,1,1,1 };
	ball->GetTransform()->scale = { 0.25f, 0.25f, 1 };
	SphereCollider2D* ballCol = ball->AddComponent<SphereCollider2D>();
	ballCol->radius = 0.4f;
	RigidBody2D* ballRb = ball->AddComponent<RigidBody2D>();
	ballRb->bounce = 0.8f;
	ballRb->drag = 0;
	ballRb->force += {-90, 0};
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