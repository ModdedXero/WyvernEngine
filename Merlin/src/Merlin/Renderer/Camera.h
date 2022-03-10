#pragma once

#include <Merlin/Core/Scene/Transform.h>

#include <glm/glm.hpp>

namespace Merlin::Renderer
{
	struct Camera
	{
		Camera();

		glm::mat4 view;
		glm::mat4 projection;
		Vector3 offset;

		Transform* transform;

		void RecalculateMatrix();
		void SetShaderMatrix();

		static Camera* main;
	};
}