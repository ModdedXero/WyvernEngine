#include "wvpch.h"
#include "Material.h"

#include <glad.h>
#include <yaml-cpp/yaml.h>

namespace Wyvern
{
	Material::Material()
		: m_Shader(nullptr)
	{
		
	}

	Material::Material(Tools::FileSystem material)
		: m_Shader(nullptr)
	{
		if (material.IsExtension(".material"))
		{
			// Load Material
		}
		else
		{
			if (material.IsDirectory())
			{
				YAML::Emitter out;

				out << YAML::BeginMap;
				out << YAML::Key << "Shader" << YAML::Value << "";
				out << YAML::EndMap;

				material /= "newMaterial.material";
				material.WriteFile(out.c_str());
			}
		}
	}

	void Material::SetShader(Tools::FileSystem& shaderPath)
	{
		m_ShaderPath = shaderPath;

		if (m_Shader) glDeleteProgram(m_Shader->ID);

		m_Shader = new Shader(shaderPath);
	}
}