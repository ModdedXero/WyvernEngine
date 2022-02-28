#pragma once

#include <glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Merlin
{
	class Shader
	{
	public:
		unsigned int ID;

		Shader();
		Shader(const char* vertSource, const char* fragSource, const char* geoSource = nullptr);

		Shader& Use();

		void SetFloat(const char* name, float value);
		void SetInteger(const char* name, int value);
		void SetVector2f(const char* name, const glm::vec2& value);
		void SetVector3f(const char* name, const glm::vec3& value);
		void SetVector4f(const char* name, const glm::vec4& value);
		void SetMatrix4(const char* name, const glm::mat4& matrix);
	private:
		void CheckCompileErrors(unsigned int object, std::string type);
	};
}