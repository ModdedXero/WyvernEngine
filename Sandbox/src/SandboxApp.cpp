#include "Merlin.h"

#include "ExampleLayer.h"
#include "RelicLayer.h"

using namespace Merlin;
using namespace Merlin::Renderer;

class SandboxApp : public Application
{
public:
	SandboxApp()
	{
		ResourceManager::LoadShader("..\\Sandbox\\Assets\\Shader\\FlatShader.vert",
			"..\\Sandbox\\Assets\\Shader\\FlatShader.frag", nullptr, "FlatShader");

		PushLayer(new RelicLayer());
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