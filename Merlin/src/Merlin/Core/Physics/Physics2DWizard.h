#pragma once

#include <Merlin/Scene/Wizard.h>

namespace Merlin
{
	class Physics2DWizard : public Wizard
	{
	public:
		void OnUpdate(Timestep ts) const override;
	};
}