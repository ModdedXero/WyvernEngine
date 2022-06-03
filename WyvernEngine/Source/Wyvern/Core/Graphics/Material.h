#pragma once

#include "Shader.h"

#include <Wyvern/Core/UUID.h>
#include <Wyvern/Tools/FileSystem.h>

namespace Wyvern
{
	struct Material
	{
	public:
		Material(Tools::FileSystem& shaderPath);

		const UUID uuid = UUID();

		Shader shader;
	private:
		Tools::FileSystem m_ShaderPath;
	};
}