#pragma once

#include "Shader.h"

#include <Wyvern/Core/Scene/Component.h>
#include <Wyvern/Core/Math/Vector.h>

namespace Wyvern
{
	struct Material
	{
		Ref<Shader> shader;
		unsigned int sortValue = 2000;

		Material operator<(const Material& other)
		{
			return other.sortValue < sortValue ? other : *this;
		}
	};
}