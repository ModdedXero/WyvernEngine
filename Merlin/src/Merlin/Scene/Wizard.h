#pragma once

#include <Merlin/Core/Timestep.h>
#include <Merlin/Scene/Entity.h>
#include <Merlin/Scene/EntityList.h>

namespace Merlin
{
	class Wizard
	{
	public:
		Wizard();
		virtual ~Wizard();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(Timestep ts) const = 0;
	};
}