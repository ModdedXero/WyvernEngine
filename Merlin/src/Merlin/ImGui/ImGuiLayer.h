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
		void OnUpdate(Timestep ts) override;
		void OnEvent(Events::Event& event) override;
	};
}