#include "Merlin.h"

#include "EditorLayer.h"

using namespace Merlin;
using namespace Merlin::Editor;

class ExcaliburApp : public Application
{
public:
	ExcaliburApp()
	{
		ResourceManager::LoadShader("./assets/shader/standardshader.vert",
			"./assets/shader/standardshader.frag", nullptr, "StandardShader");
		ResourceManager::LoadShader("./assets/shader/fontshader.vert",
			"./assets/shader/fontshader.frag", nullptr, "FontShader");

		ResourceManager::LoadMaterial("StandardShader", "StandardMaterial");
		ResourceManager::LoadMaterial("FontShader", "StandardFontMaterial")->sortValue = 100;

		PushLayer(new EditorLayer());
	}

	~ExcaliburApp()
	{

	}
};

int main()
{
	Scope<ExcaliburApp> app = CreateScope<ExcaliburApp>();
	app->Run();
}