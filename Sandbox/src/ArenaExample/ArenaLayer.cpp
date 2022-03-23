#include "ArenaLayer.h"

#include "imgui.h"

using namespace Merlin;
using namespace Merlin::Renderer;

int TileMap[10][10] =
{
	{2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
	{2, 1, 1, 1, 1, 1, 1, 1, 1, 2},
	{2, 1, 1, 1, 1, 1, 1, 1, 1, 2},
	{2, 1, 1, 1, 1, 1, 1, 1, 1, 2},
	{2, 1, 1, 1, 1, 1, 1, 1, 1, 2},
	{2, 1, 1, 1, 1, 1, 1, 1, 1, 2},
	{2, 1, 1, 1, 1, 1, 1, 1, 1, 2},
	{2, 1, 1, 1, 1, 1, 1, 1, 1, 2},
	{2, 1, 1, 1, 1, 1, 1, 1, 1, 2},
	{2, 2, 2, 2, 2, 2, 2, 2, 2, 2}
};

ArenaLayer::ArenaLayer()
	: Layer("Arena Layer"), fps(0), player(nullptr)
{

}

class Wall : public Entity
{
public:
	void OnAttach() override
	{
		GetTransform()->scale = { 0.5f, 0.5f, 0.5f };
		Material2D* mat = AddComponent<Material2D>();
		mat->shader = ResourceManager::GetShader("FlatShader");
		mat->subTexture = ResourceManager::GetSubTexture("Wall");
		RigidBody2D* rb = AddComponent<RigidBody2D>();
		rb->bodyType = RigidBody2D::PhysicsBody::Static;
		rb->mass = 0.0f;
		AddComponent<BoxCollider2D>()->size = GetTransform()->scale;
	}

	void OnCollision2D(const Collision2D& collision) override
	{
		DEBUG_LOG("Test2");
	}
};

void ArenaLayer::OnAttach()
{
	for (int row = 9; row >= 0; row--)
	{
		for (int col = 0; col < 10; col++)
		{
			if (TileMap[col][row] == 1)
			{
				Entity* tile = Scene::CreateEntity<Entity>();
				tile->GetTransform()->scale = { 0.5f, 0.5f, 0.5f };
				tile->GetTransform()->position += Vector2(row - 1, -col + 1);
				Material2D* mat = tile->AddComponent<Material2D>();
				mat->shader = ResourceManager::GetShader("FlatShader");
				mat->subTexture = ResourceManager::GetSubTexture("Floor");
			}
			else if (TileMap[col][row] == 2)
			{
				Wall* tile = Scene::CreateEntity<Wall>();
				tile->GetTransform()->position += Vector2(row - 1, -col + 1);
			}
		}
	}

	player = Scene::CreateEntity<PlayerEntity>();
}

void ArenaLayer::OnUpdate(Timestep ts)
{
	fps = ts.GetFPS();
	player->MovePlayer(ts.GetDeltaTime());
}

void ArenaLayer::OnImGuiRender()
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