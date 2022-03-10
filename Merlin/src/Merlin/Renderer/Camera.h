#pragma once

#include <Merlin/Core/Scene/Transform.h>

#include <glm/glm.hpp>

namespace Merlin::Renderer
{
	struct Camera
	{
		Camera();

		void RecalculateMatrix();
		void SetShaderMatrix();

		glm::mat4 view;
		glm::mat4 projection;

		Transform* transform;

		static Camera* main;
	};
}