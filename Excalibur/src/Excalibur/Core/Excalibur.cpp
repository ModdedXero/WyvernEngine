#include "Merlin.h"

#include "EditorLayer.h"

using namespace Merlin;
using namespace Merlin::Editor;

class ExcaliburApp : public Application
{
public:
	ExcaliburApp()
	{
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