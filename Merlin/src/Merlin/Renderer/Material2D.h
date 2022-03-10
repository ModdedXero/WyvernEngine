#pragma once

#include "Shader.h"
#include "Texture2D.h"
#include "SubTexture2D.h"

#include <Merlin/Core/Math/Vector.h>

namespace Merlin::Renderer
{
	struct Material2D
	{
		unsigned int shader = -1;
		unsigned int texture = -1;
		SubTexture2D* subTexture = nullptr;
		Vector4 color = { 1.0f, 1.0f, 1.0f, 1.0f };
	};
}