#include "Merlin.h"

#include <memory>

using namespace Merlin;
using namespace Merlin::Events;

class CameraController
{
public:
	Camera camera;
	float speed = 0.03f;

	CameraController()
	{
		camera.transform.z = -3.0f;
	}

	void MoveCamera()
	{
		if (Input::IsKey(KeyCode::A))
		{
			camera.transform.x += speed;
		}
		if (Input::IsKey(KeyCode::D))
		{
			camera.transform.x -= speed;
		}

		if (Input::IsKey(KeyCode::W))
		{
			camera.transform.y -= speed;
		}
		if (Input::IsKey(KeyCode::S))
		{
			camera.transform.y += speed;
		}

		Camera::Main().RecalculateMatrix();
		Camera::Main().SetShaderMatrix();
	}
};

class ExampleLayer : public Layer
{
	CameraController* cControl;

	Entity* player;
	Entity* gameFloor;

	void OnAttach() override
	{
		// Camera
		cControl = new CameraController();

		// Player
		player = Entity::CreateEntity();
		Transform* playerTs = player->GetTransform();
		playerTs->scale = { 0.25f, 0.25f, 1.0f };
		playerTs->position = { -2.5f, 0, 0 };
		Material2D* playerMat = player->AddComponent<Material2D>();
		playerMat->shader = ResourceManager::GetShader("FlatShader").ID;
		playerMat->color = { 0.3f, 0.6f, 0.9f, 1.0f };

		// Floor
		gameFloor = Entity::CreateEntity();
		Transform* floorTs = gameFloor->GetTransform();
		floorTs->scale = { 4.0f, 0.25f, 1.0f };
		floorTs->position = { 0, -1.5f, 0 };
		Material2D* floorMat = gameFloor->AddComponent<Material2D>();
		floorMat->shader = ResourceManager::GetShader("FlatShader").ID;
		floorMat->color = { 0.7f, 0.3f, 0.4f, 1.0f };
	}

	void OnUpdate(Timestep ts) override
	{
		cControl->MoveCamera();
	}
};

class SandboxApp : public Application
{
public:
	SandboxApp()
	{
		ResourceManager::LoadShader("E:\\Programming\\VisualStudio\\Projects\\Merlin\\Sandbox\\Assets\\Shader\\FlatShader.vert",
			"E:\\Programming\\VisualStudio\\Projects\\Merlin\\Sandbox\\Assets\\Shader\\FlatShader.frag", nullptr, "FlatShader");

		ResourceManager::LoadTexture("E:\\Programming\\VisualStudio\\Projects\\Merlin\\Sandbox\\Assets\\Texture\\Default.png", true, true, "Default");

		int samplers[32];
		for (int i = 0; i < 32; i++)
			samplers[i] = i;
		ResourceManager::GetShader("FlatShader").SetIntArray("uTextures", 32, samplers);

		PushLayer(new ExampleLayer());
	}

	~SandboxApp()
	{

	}
};

int main()
{
	std::unique_ptr<SandboxApp> app = std::make_unique<SandboxApp>();
	app->Run();
}