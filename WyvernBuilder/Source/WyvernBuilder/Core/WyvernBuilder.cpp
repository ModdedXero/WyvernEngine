#include "Wyvern.h"

#include "BuilderLayer.h"

using namespace Wyvern;

class WyvernBuilder : public Application
{
public:
	WyvernBuilder()
	{
		AssetManager::LoadShader("../assets/shader/standardshader.vert",
			"../assets/shader/standardshader.frag", nullptr, "StandardShader");
		AssetManager::LoadShader("../assets/shader/fontshader.vert",
			"../assets/shader/fontshader.frag", nullptr, "FontShader");

		AssetManager::LoadMaterial("StandardShader", "StandardMaterial");

		PushLayer(new BuilderLayer());
	}

	~WyvernBuilder()
	{

	}
};

int main()
{
	Scope<WyvernBuilder> app = CreateScope<WyvernBuilder>();
	app->Run();
}