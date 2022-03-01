#pragma once

#include <Merlin/Core/Events/Event.h>
#include <Merlin/Core/Timestep.h>

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
		virtual void OnUpdate(Timestep ts) {}

		virtual void OnEvent(Events::Event& event) {}

		inline const std::string& GetName() const { return m_DebugName; }
	private:
		std::string m_DebugName;
	};
}