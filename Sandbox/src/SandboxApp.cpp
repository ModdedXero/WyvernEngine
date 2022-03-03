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

struct Test
{
	int nice = 0;

	void print()
	{
		ML_LOG_INFO(nice);
	}
};

struct Test2
{
	int nice = 1;
	void print()
	{
		ML_LOG_INFO(nice);
	}
};

class ExampleLayer : public Layer
{
	CameraController* cControl;
	int loopTime = 0;
	Entity* box;

	void OnAttach() override
	{
		cControl = new CameraController();
		ML_LOG_INFO("Example");

		box = Scene::CreateEntity();

		Material2D* mat = box->AddComponent<Material2D>();

		mat->shader = ResourceManager::GetShader("FlatShader").ID;
		mat->texture = ResourceManager::GetTexture("Default").ID;

		int count = 0;
		for (float x = -10.0f; x < 10.0f; x += 0.25f)
		{
			for (float y = -10.0f; y < 10.0f; y += 0.25f)
			{
				count++;
				Entity* griddss = Scene::CreateEntity();
				Material2D* gridmat = griddss->AddComponent<Material2D>();
				Transform* gridTs = griddss->GetTransform();

				gridTs->position = Vector3(x * 2, y * 2, 0.0f);
				gridTs->scale = Vector3(0.1f, 0.1f, 1.0f);

				gridmat->shader = ResourceManager::GetShader("FlatShader").ID;
				gridmat->texture = ResourceManager::GetTexture("Default").ID;
			}
		}
		ML_LOG_INFO(count);
	}

	void OnUpdate(Timestep ts) override
	{
		//for (float x = -10.0f; x < 10.0f; x += 0.25f)
		//{
		//	for (float y = -10.0f; y < 10.0f; y += 0.25f)
		//	{
		//		Renderer2D::DrawQuad(Vector3(x, y, 0.0f), Vector2(0.1f, 0.1f),
		//			Vector4(0, 0, 1, 1.0f));
		//	}
		//}

		Transform* boxTs = box->GetTransform();
		boxTs->position = Vector3(glm::sin(ts.GetSeconds()), -glm::sin(ts.GetSeconds()), 0);
		boxTs->scale = Vector3(1, 1, 1);

		for (Entity* ent : ComponentList<Material2D>())
		{
			ent->GetComponent<Material2D>()->Render(*ent->GetTransform());
		}

		ML_LOG_INFO(1.0f / ts.GetDeltaTime());

		cControl->MoveCamera();
	}

	void OnEvent(Event& event) override
	{
		// std::cout << event.ToString() << std::endl;
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

		// Test

		//

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