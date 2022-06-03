#pragma once

#include "Shader.h"

#include <Wyvern/Core/UUID.h>
#include <Wyvern/Tools/FileSystem.h>

namespace Wyvern
{
	struct Material
	{
	public:
		Material();
		Material(Tools::FileSystem& material);

	public:
		UUID GetUUID() const { return m_UUID; }
		Shader GetShader() const { return *m_Shader; }

	public:
		void SetShader(Tools::FileSystem& shaderPath);

	private:
		UUID m_UUID;
		Tools::FileSystem m_ShaderPath;
		Shader* m_Shader;
	};
}