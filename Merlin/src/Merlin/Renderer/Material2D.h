#pragma once

#include "Shader.h"
#include "Texture2D.h"
#include "SubTexture2D.h"

#include <Merlin/Core/Math/Vector.h>

namespace Merlin::Renderer
{
	struct Material2D
	{
		Shader* shader = nullptr;
		Texture2D* texture = nullptr;
		SubTexture2D* subTexture = nullptr;

		Vector4 color = { 1.0f, 1.0f, 1.0f, 1.0f };
	};
}