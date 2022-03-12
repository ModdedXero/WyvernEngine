#pragma once

#include <Merlin/Core/Layer.h>
#include <Merlin/Core/Timestep.h>

namespace Merlin
{
	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnAttach() override;
		void OnDetach() override;

		void Begin();
		void End();
	};
}