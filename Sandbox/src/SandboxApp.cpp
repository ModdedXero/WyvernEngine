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
		camera.transform.z = -8.0f;
	}
};

class PlayerEntity : public Entity
{
public:
	PlayerEntity(EntityID id, ComponentMask mask)
		: Entity(id, mask), transform(nullptr), rb(nullptr), collider(nullptr), mat(nullptr)
	{

	}

	Transform* transform;
	RigidBody2D* rb;
	BoxCollider2D* collider;
	Material2D* mat;

	void InitDefaultComponents() override
	{
		transform = GetTransform();
		transform->scale = { 0.25f, 0.25f, 1.0f };
		transform->position = { -4.0f, 0, 0 };
		rb = AddComponent<RigidBody2D>();
		collider = AddComponent<BoxCollider2D>();
		collider->size = transform->scale;
		mat = AddComponent<Material2D>();
		mat->shader = ResourceManager::GetShader("FlatShader").ID;
		mat->color = { 0.3f, 0.6f, 0.9f, 1.0f };
	}

	void OnCollision2D(const Collision2D& collision) override
	{
		rb->velocity = Vector3();
		transform->position = collision.aTransform->position;
	}
};

class ExampleLayer : public Layer
{
	CameraController* cControl;

	PlayerEntity* player;
	Entity* gameFloor;

	Transform* playerTs;

	void OnAttach() override
	{
		// Camera
		cControl = new CameraController();

		// Player
		player = Scene::CreateEntity<PlayerEntity>();

		// Floor
		gameFloor = Entity::CreateEntity();
		Transform* floorTs = gameFloor->GetTransform();
		floorTs->scale = { 6.0f, 0.5f, 1.0f };
		floorTs->position = { 0, -3.0f, 0 };
		BoxCollider2D* box2 = gameFloor->AddComponent<BoxCollider2D>();
		box2->size = floorTs->scale;
		Material2D* floorMat = gameFloor->AddComponent<Material2D>();
		floorMat->shader = ResourceManager::GetShader("FlatShader").ID;
		floorMat->color = { 0.7f, 0.3f, 0.4f, 1.0f };
	}

	void OnUpdate(Timestep ts) override
	{

	}
};

class SandboxApp : public Application
{
public:
	SandboxApp()
	{
		ResourceManager::LoadShader("C:\\Programming\\VisualStudio\\Projects\\Merlin\\Sandbox\\Assets\\Shader\\FlatShader.vert",
			"C:\\Programming\\VisualStudio\\Projects\\Merlin\\Sandbox\\Assets\\Shader\\FlatShader.frag", nullptr, "FlatShader");

		ResourceManager::LoadTexture("C:\\Programming\\VisualStudio\\Projects\\Merlin\\Sandbox\\Assets\\Texture\\Default.png", true, true, "Default");

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