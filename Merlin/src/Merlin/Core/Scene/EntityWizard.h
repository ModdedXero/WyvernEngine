#pragma once

#include "Wizard.h"

namespace Merlin
{
	class EntityWizard : public Wizard
	{
	public:
		virtual void OnUpdate() override;
		virtual void OnFixedUpdate() override;
		virtual void OnEvent(Events::Event& e) override;
	};
}