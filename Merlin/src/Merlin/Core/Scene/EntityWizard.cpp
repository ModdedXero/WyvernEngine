#include "EntityWizard.h"

#include "EntityList.h"

namespace Merlin
{
	void EntityWizard::OnUpdate()
	{
		for (Entity* ent : EntityList())
		{
			ent->OnUpdate();
		}
	}

	void EntityWizard::OnFixedUpdate()
	{
		for (Entity* ent : EntityList())
		{
			ent->OnFixedUpdate();
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