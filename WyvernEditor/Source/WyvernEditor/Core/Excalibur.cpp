#include "Wyvern.h"

#include "EditorLayer.h"

using namespace Wyvern;
using namespace Wyvern::Editor;

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