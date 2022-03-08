#pragma once

#include <Merlin/Core/Math/Vector.h>

namespace Merlin::Renderer
{
	struct Material2D
	{
		unsigned int shader = -1;
		unsigned int texture = -1;
		Vector4 color = { 1.0f, 1.0f, 1.0f, 1.0f };
	};
}