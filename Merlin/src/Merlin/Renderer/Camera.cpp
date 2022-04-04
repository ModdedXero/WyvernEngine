#include "mlpch.h"
#include "Camera.h"

#include "ResourceManager.h"

#include <Merlin/Core/Application.h>

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>

namespace Merlin::Renderer
{
	Camera* Camera::s_Main = nullptr;

	Camera::Camera()
		: projection(1.0f), view(1.0f)
	{
		if (s_Main == nullptr) s_Main = this;

		projection = glm::perspective(glm::radians(60.0f),
			(float)Application::Get().GetWindow().GetWidth() / (float)Application::Get().GetWindow().GetHeight(), 0.1f, 100.0f);
	}

	void Camera::SetShaderMatrices()
	{
		view = glm::translate(glm::mat4(1.0f), (-GetTransform()->position + -offset).glmPosition());

		// TODO: Loop through all Shaders and update their Matrices
		for (auto& iter : ResourceManager::GetShaders())
			iter.second->SetMatrix4("projectionViewModel", projection * view * glm::mat4(1.0f));

		auto test = projection * view * glm::mat4(1.0f) * glm::vec4(GetTransform()->position.glmPosition(), 1.0f);
	}


	Vector2 Camera::WorldToScreenPoint(Vector3& pos)
	{
		Camera* cam = Camera::GetMain();
		Window::Window& window = Application::Get().GetWindow();

		auto point = cam->projection * cam->view * glm::mat4(1.0f) * glm::vec4(pos.x, pos.y, 1.0f, 1.0f);

		float xPos = ((point.x + 8) / 16) * window.GetWidth();
		float yPos = window.GetHeight() - (((point.y + 8) / 16) * window.GetHeight());

		return Vector2(xPos, yPos);
	}
}