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

		std::string shaderCode;
		std::string vertCode, fragCode, geoCode;

		try
		{
			std::ifstream shaderFile(shaderPath);
			std::stringstream shaderStream;

			shaderStream << shaderFile.rdbuf();
			shaderFile.close();

			shaderCode = shaderStream.str();

			size_t vertexIndex = shaderCode.rfind("##VERTEX##");
			size_t fragmentIndex = shaderCode.rfind("##FRAGMENT##");
			size_t geoIndex = shaderCode.rfind("##GEOMETRY##");

			if (vertexIndex != std::string::npos && fragmentIndex != std::string::npos)
			{
				vertCode = shaderCode.substr(vertexIndex + sizeof("##VERTEX##\n"), fragmentIndex);
			}
			else if (vertexIndex != std::string::npos && geoIndex != std::string::npos)
			{
				vertCode = shaderCode.substr(vertexIndex + sizeof("##VERTEX##\n"), geoIndex);
			}

			if (fragmentIndex != std::string::npos && geoIndex != std::string::npos)
			{
				fragCode = shaderCode.substr(fragmentIndex + sizeof("##FRAGMENT##\n"), geoIndex);
			}
			else
			{
				fragCode = shaderCode.substr(fragmentIndex + sizeof("##FRAGMENT##\n"));
			}

			if (geoIndex != std::string::npos)
			{
				geoCode = shaderCode.substr(geoIndex + sizeof("##GEOMETRY##\n"));
			}

		}
		catch (const std::exception& e)
		{
			DEBUG_LOG_ERROR(e.what());
		}

		const char* vShaderCode = vertCode.c_str();
		const char* fShaderCode = fragCode.c_str();
		const char* gShaderCode = geoCode.c_str();


		m_Shader = new Shader(vShaderCode, fShaderCode, !geoCode.empty() ? gShaderCode : nullptr);
	}
}