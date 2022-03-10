#include "mlpch.h"
#include "Camera.h"

#include "ResourceManager.h"

#include <Merlin/Core/Application.h>

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>

namespace Merlin::Renderer
{
	Camera* Camera::main = nullptr;

	Camera::Camera()
		: projection(1.0f), view(1.0f), transform(nullptr)
	{
		if (main == nullptr) main = this;

		projection = glm::perspective(glm::radians(60.0f),
			(float)Application::Get().GetWindow().GetWidth() / (float)Application::Get().GetWindow().GetHeight(), 0.1f, 100.0f);
	}

	void Camera::RecalculateMatrix()
	{
		view = (-transform->position + -offset).localToWorldMatrix();
	}

	void Camera::SetShaderMatrix()
	{
		// TODO: Loop through all Shaders and update their Matrices
		ResourceManager::GetShader("FlatShader").SetMatrix4("view", view);
		ResourceManager::GetShader("FlatShader").SetMatrix4("projection", projection);
	}
}