#pragma once

#include "Component.h"
#include "Transform.h"

#include <Merlin/Core/Graphics/Shader.h>

#include <glm/glm.hpp>

namespace Merlin
{
	struct Camera : public Component
	{
		Camera();
		~Camera() {}

		glm::mat4 view;
		glm::mat4 projection;

		void SetShaderMatrices(Ref<Shader> shader);

		static Camera* GetMain() { return s_Main; }
		static Vector2 WorldToScreenPoint(Vector3& pos);
	private:
		static Camera* s_Main;
	};
}