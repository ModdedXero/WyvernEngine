#pragma once

#include "Entity.h"
#include "EntityList.h"

#include <Merlin/Core/Timestep.h>

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