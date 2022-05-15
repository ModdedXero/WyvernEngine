#include <Wyvern.h>

#include "BuilderLayer.h"

using namespace Wyvern;
using namespace Wyvern::Utils;

class WyvernBuilder : public Application
{
public:
	WyvernBuilder(const ApplicationSpecification& specification)
		: Application(specification)
	{
		AssetManager::LoadShader(specification.ResourcesPath / "/shader/standardshader.vert",
			specification.ResourcesPath / "/shader/standardshader.frag", "", "StandardShader");
		AssetManager::LoadShader(specification.ResourcesPath / "/shader/fontshader.vert",
			specification.ResourcesPath / "/shader/fontshader.frag", "", "FontShader");

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

	Scope<WyvernBuilder> app = CreateScope<WyvernBuilder>(specification);
	app->Run();
	return 0;
}