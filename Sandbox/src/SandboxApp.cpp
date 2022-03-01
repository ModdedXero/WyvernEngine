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
	int loopTime = 0;

	void OnAttach() override
	{
		cControl = new CameraController();
		ML_LOG_INFO("Example");

		ResourceManager::LoadShader("E:\\Programming\\VisualStudio\\Projects\\Merlin\\Sandbox\\Assets\\Shader\\FlatShader.vert",
			"E:\\Programming\\VisualStudio\\Projects\\Merlin\\Sandbox\\Assets\\Shader\\FlatShader.frag", nullptr, "FlatShader");

		ResourceManager::LoadTexture("E:\\Programming\\VisualStudio\\Projects\\Merlin\\Sandbox\\Assets\\Texture\\Default.png", true, true, "Default");

		int samplers[32];
		for (int i = 0; i < 32; i++)
			samplers[i] = i;
		ResourceManager::GetShader("FlatShader").SetIntArray("uTextures", 32, samplers);
	}

	void OnUpdate(Timestep ts) override
	{
		glm::mat4 model = glm::mat4(1.0f);

		ResourceManager::GetShader("FlatShader").SetMatrix4("model", model);
		cControl->MoveCamera();

		for (float x = -10.0f; x < 10.0f; x += 0.25f)
		{
			for (float y = -10.0f; y < 10.0f; y += 0.25f)
			{
				Renderer2D::DrawQuad(Vector3(x, y, 0.0f), Vector2(0.1f, 0.1f),
					Vector4(0, 0, 1, 1.0f));
			}
		}

		Renderer2D::DrawQuad(Vector3(glm::sin(ts.GetSeconds()), -glm::sin(ts.GetSeconds()), 0), Vector2(1, 1), ResourceManager::GetTexture("Default").ID);
		glUseProgram(ResourceManager::GetShader("FlatShader").ID);
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