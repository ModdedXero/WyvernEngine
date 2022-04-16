#pragma once

#include "Timestep.h"

#include <Merlin/Events/Event.h>

#include <string>

namespace Merlin
{
	class Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate() {}
		virtual void OnFixedUpdate() {}
		virtual void OnUIRender() {}

		virtual void OnEvent(Events::Event& event) {}

		inline const std::string& GetName() const { return m_DebugName; }
	private:
		std::string m_DebugName;
	};
}