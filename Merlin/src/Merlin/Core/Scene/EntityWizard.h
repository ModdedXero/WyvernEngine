#pragma once

#include "Wizard.h"

namespace Merlin
{
	class EntityWizard : public Wizard
	{
	public:
		virtual void OnUpdate(Timestep ts) override;
		virtual void OnFixedUpdate(Timestep ts) override;
		virtual void OnEvent(Events::Event& e) override;
	};
}