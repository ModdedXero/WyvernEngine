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

		ResourceManager::LoadTexture("..\\Sandbox\\Assets\\Texture\\tileset.png", true, true, "Dungeon");

		ResourceManager::LoadSubTexture("Floor", "Dungeon", { 1,14 }, { 1,1 }, { 32,32 });
		ResourceManager::LoadSubTexture("Wall", "Dungeon", { 25,13 }, { 1,1 }, { 32,32 });
		ResourceManager::LoadSubTexture("Player", "Dungeon", { 17,6 }, { 1,1 }, { 32,32 });

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