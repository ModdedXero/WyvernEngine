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
		: m_Shader(nullptr), m_MaterialPath(material)
	{
		if (material.IsExtension(".material"))
		{
			LoadMaterial();
		}
		else
		{
			if (material.IsDirectory())
			{
				YAML::Emitter out;

				out << YAML::BeginMap;
				out << YAML::Key << "Shader" << YAML::Value << "";
				out << YAML::EndMap;

				m_MaterialPath /= "newMaterial.material";
				SaveMaterial();
			}
		}
	}

	void Material::SetShader(Tools::FileSystem& shaderPath)
	{
		m_ShaderPath = shaderPath;

		if (m_Shader) glDeleteProgram(m_Shader->ID);

		m_Shader = new Shader(shaderPath);
	}

	void Material::LoadMaterial()
	{
		std::string material = m_MaterialPath.ReadFile();

		YAML::Node in = YAML::Load(material);
		m_ShaderPath = in["Shader"].as<std::string>();

		if (m_ShaderPath.IsExtension(".glsl"))
		{
			SetShader(m_ShaderPath);
		}
	}

	void Material::SaveMaterial()
	{
		YAML::Emitter out;

		out << YAML::BeginMap;
		out << YAML::Key << "Shader" << YAML::Value << m_ShaderPath;
		out << YAML::EndMap;

		m_MaterialPath.WriteFile(out.c_str());
	}
}