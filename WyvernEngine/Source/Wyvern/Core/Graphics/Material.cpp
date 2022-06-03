#include "wvpch.h"
#include "Material.h"

namespace Wyvern
{
	Material::Material(Tools::FileSystem& shaderPath)
		: m_ShaderPath(shaderPath)
	{
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
				vertCode = shaderCode.substr(vertexIndex + sizeof("##VERTEX##"), fragmentIndex);
			}
			else if (vertexIndex != std::string::npos && geoIndex != std::string::npos)
			{
				vertCode = shaderCode.substr(vertexIndex + sizeof("##VERTEX##"), geoIndex);
			}

			if (fragmentIndex != std::string::npos && geoIndex != std::string::npos)
			{
				fragCode = shaderCode.substr(fragmentIndex + sizeof("##FRAGMENT##"), geoIndex);
			}
			else
			{
				fragCode = shaderCode.substr(fragmentIndex + sizeof("##FRAGMENT##"));
			}

			if (geoIndex != std::string::npos)
			{
				geoCode = shaderCode.substr(geoIndex + sizeof("##GEOMETRY##"));
			}

		}
		catch (const std::exception& e)
		{
			DEBUG_LOG_ERROR("ResourceManager: ", e.what());
		}

		const char* vShaderCode = vertCode.c_str();
		const char* fShaderCode = fragCode.c_str();
		const char* gShaderCode = geoCode.c_str();


		shader = Shader(vShaderCode, fShaderCode, !geoCode.empty() ? gShaderCode : nullptr);
	}
}