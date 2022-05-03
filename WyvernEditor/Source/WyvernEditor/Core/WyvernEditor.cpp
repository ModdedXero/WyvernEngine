#include "Wyvern.h"

#include "EditorLayer.h"

using namespace Wyvern;
using namespace Wyvern::Editor;

class WyvernEditor : public Application
{
public:
	WyvernEditor()
	{
		AssetManager::LoadShader("../assets/shader/standardshader.vert",
			"../assets/shader/standardshader.frag", nullptr, "StandardShader");
		AssetManager::LoadShader("../assets/shader/fontshader.vert",
			"../assets/shader/fontshader.frag", nullptr, "FontShader");

		AssetManager::LoadMaterial("StandardShader", "StandardMaterial");

		PushLayer(new EditorLayer());
	}

	~WyvernEditor()
	{

	}
};

int main()
{
	Scope<WyvernEditor> app = CreateScope<WyvernEditor>();
	app->Run();
}