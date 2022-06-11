#include <Wyvern.h>
#include <WyvernBuilder/Core/BuilderLayer.h>

using namespace Wyvern;

class WyvernBuilder : public Application
{
public:
	WyvernBuilder(const ApplicationSpecification& specification)
		: Application(specification)
	{
		AssetManager::LoadMaterial(specification.ResourcesPath / "material/defaultmaterial.material");

		Project::LoadProject(specification.AssetsPath / "project.wproj");

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