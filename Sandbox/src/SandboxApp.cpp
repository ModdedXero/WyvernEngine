#include "Merlin.h"

#include <memory>

using namespace Merlin;
using namespace Merlin::Events;

class CameraController
{
public:
	Camera camera;

	CameraController()
	{
		camera.transform.z = -3.0f;
	}

	void MoveCamera()
	{
		if (Input::IsKey(KeyCode::A))
		{
			camera.transform.x += 0.01f;
		}
		if (Input::IsKey(KeyCode::D))
		{
			camera.transform.x -= 0.01f;
		}

		if (Input::IsKey(KeyCode::W))
		{
			camera.transform.y -= 0.01f;
		}
		if (Input::IsKey(KeyCode::S))
		{
			camera.transform.y += 0.01f;
		}

		Camera::Main().RecalculateMatrix();
		Camera::Main().SetShaderMatrix();
	}
};

class ExampleLayer : public Layer
{
	CameraController* cControl;

	void OnAttach() override
	{
		cControl = new CameraController();
		ML_LOG_INFO("Example");
	}

	void OnUpdate() override
	{
		glm::mat4 model = glm::mat4(1.0f);

		ResourceManager::GetShader("FlatShader").SetMatrix4("model", model);
		cControl->MoveCamera();

		for (float x = -10.0f; x < 10.0f; x += 0.25f)
		{
			for (float y = -10.0f; y < 10.0f; y += 0.25f)
			{
				Renderer2D::DrawQuad(Vector3(x, y, 0.0f), Vector2(0.1f, 0.1f),
					Vector4(0.5f, 0.75f, 0.25f, 1.0f));
			}
		}

		Renderer2D::DrawQuad(Vector3(0.0f, 0.0f, 0.0f), Vector2(1, 1), Vector4(0.7f, 0.4f, 1.0f, 1.0f));
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
		ResourceManager::LoadShader("C:\\Programming\\VisualStudio\\Projects\\Merlin\\Sandbox\\Assets\\Shader\\FlatShader.vert",
			"C:\\Programming\\VisualStudio\\Projects\\Merlin\\Sandbox\\Assets\\Shader\\FlatShader.frag", nullptr, "FlatShader");

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