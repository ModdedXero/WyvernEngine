#include "EntityWizard.h"

#include "EntityList.h"

namespace Merlin
{
	void EntityWizard::OnUpdate(Timestep ts)
	{
		for (Entity* ent : EntityList())
		{
			ent->OnUpdate(ts);
		}
	}

	void EntityWizard::OnFixedUpdate(Timestep ts)
	{
		for (Entity* ent : EntityList())
		{
			ent->OnFixedUpdate(ts);
		}
	}

	void EntityWizard::OnEvent(Events::Event& e)
	{
		for (Entity* ent : EntityList())
		{
			ent->OnEvent(e);
		}
	}
}