#include "Merlin.h"

#include "EditorLayer.h"

using namespace Merlin;
using namespace Merlin::Editor;

class ExcaliburApp : public Application
{
public:
	ExcaliburApp()
	{
		AssetManager::LoadShader("../assets/shader/standardshader.vert",
			"../assets/shader/standardshader.frag", nullptr, "StandardShader");
		AssetManager::LoadShader("../assets/shader/fontshader.vert",
			"../assets/shader/fontshader.frag", nullptr, "FontShader");

		AssetManager::LoadMaterial("StandardShader", "StandardMaterial");
		AssetManager::LoadMaterial("FontShader", "StandardFontMaterial")->sortValue = 100;

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