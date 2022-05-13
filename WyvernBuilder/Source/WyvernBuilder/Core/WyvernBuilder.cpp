#include <Wyvern.h>

#include "BuilderLayer.h"

using namespace Wyvern;

class WyvernBuilder : public Application
{
public:
	WyvernBuilder(const ApplicationSpecification& specification)
		: Application(specification)
	{
		ScriptCoreManager::GenerateScriptCore();

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

int main(int argc, char** argv)
{
	ApplicationSpecification specification;

	specification.Name = "Wyvern Builder";

	if (argc > 1)
	{
		specification.ProjectName = argv[1];
		specification.ProjectPath = argv[2];
	}

	Scope<WyvernBuilder> app = CreateScope<WyvernBuilder>(specification);
	app->Run();
	return 0;
}