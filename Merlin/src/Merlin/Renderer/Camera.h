#pragma once

#include <Merlin/Core/Scene/Component.h>
#include <Merlin/Core/Scene/Transform.h>

#include <glm/glm.hpp>

namespace Merlin::Renderer
{
	struct Camera : public Component
	{
		Camera();
		~Camera() {}

		glm::mat4 view;
		glm::mat4 projection;
		Vector3 offset;

		void SetShaderMatrices();

		static Camera* GetMain() { return s_Main; }
		static Vector2 WorldToScreenPoint(Vector3& pos);
	private:
		static Camera* s_Main;
	};
}