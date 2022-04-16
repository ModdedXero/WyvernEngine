#pragma once

#include <Merlin/Core/Scene/Wizard.h>

namespace Merlin::Renderer
{
	class RenderWizard : public Wizard
	{
	public:
		void OnUpdate() override;
	};
}