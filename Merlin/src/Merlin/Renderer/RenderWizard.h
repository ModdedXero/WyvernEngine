#pragma once

#include <Merlin/Scene/Wizard.h>

namespace Merlin
{
	class RenderWizard : public Wizard
	{
	public:
		void OnUpdate(Timestep ts) const override;
	};
}