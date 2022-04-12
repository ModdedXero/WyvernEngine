#include "Merlin.h"

#include "ArenaExample/ArenaLayer.h"
#include "PongExample/PongLayer.h"

using namespace Merlin;
using namespace Merlin::Renderer;

class SandboxApp : public Application
{
public:
	SandboxApp()
	{


		ResourceManager::LoadTexture("..\\Sandbox\\Assets\\Texture\\tileset.png", true, true, "Dungeon");
		ResourceManager::LoadTexture("..\\Sandbox\\Assets\\Texture\\ball.png", true, true, "Ball");

		ResourceManager::LoadSprite("Ball", "Ball", { 0,0 }, { 1,1 }, { 32,32 });
		ResourceManager::LoadSprite("Floor", "Dungeon", { 1,14 }, { 1,1 }, { 32,32 });
		ResourceManager::LoadSprite("Wall", "Dungeon", { 25,13 }, { 1,1 }, { 32,32 });
		ResourceManager::LoadSprite("Player", "Dungeon", { 17,6 }, { 1,1 }, { 32,32 });

		PushLayer(new PongLayer());
	}

	~SandboxApp()
	{

	}
};

int main()
{
	Scope<SandboxApp> app = std::make_unique<SandboxApp>();
	app->Run();
}