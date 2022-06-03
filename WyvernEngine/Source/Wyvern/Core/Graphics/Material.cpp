#include "wvpch.h"
#include "Material.h"

#include <glad.h>

namespace Wyvern
{
	Material::Material(Tools::FileSystem& material)
		: m_Shader(nullptr)
	{
		
	}

	void Material::SetShader(Tools::FileSystem& shaderPath)
	{
		m_ShaderPath = shaderPath;

		if (m_Shader) glDeleteProgram(m_Shader->ID);

		m_Shader = new Shader(shaderPath);
	}
}