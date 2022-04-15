#include "Merlin.h"

#include "EditorLayer.h"

using namespace Merlin;

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
	Scope<ExcaliburApp> app = std::make_unique<ExcaliburApp>();
	app->Run();
}