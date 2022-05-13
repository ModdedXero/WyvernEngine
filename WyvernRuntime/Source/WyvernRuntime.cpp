#include <Wyvern.h>

#include "RuntimeLayer.h"

using namespace Wyvern;

class WyvernRuntime : public Application
{
public:
	WyvernRuntime()
	{
		PushLayer(new RuntimeLayer());
	}

	~WyvernRuntime()
	{

	}
};

int main()
{
	Scope<WyvernRuntime> app = CreateScope<WyvernRuntime>();
	app->Run();
	return 0;
}