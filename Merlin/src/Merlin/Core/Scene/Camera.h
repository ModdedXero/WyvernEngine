#pragma once

#include "Component.h"
#include "Transform.h"

#include <Merlin/Core/Graphics/Shader.h>

#include <glm/glm.hpp>

namespace Merlin
{
	enum class CameraMode
	{
		Perspective,
		Orthographic
	};

	struct Camera : public Component
	{
		Camera();
		~Camera() {}

		CameraMode GetCameraMode() { return m_CameraMode; }
		float GetOrthoSize() { return m_OrthoSize; }
		float GetFieldOfView() { return m_FieldOfView; }
		float GetClipNear() { return m_ClipNear; }
		float GetClipFar() { return m_ClipFar; }

		void SetCameraMode(CameraMode mode);
		void SetProjection(float width, float height);
		void SetOrthoSize(float orthoSize) { m_OrthoSize = orthoSize; }
		void SetFieldOfView(float fov) { m_FieldOfView = fov; }
		void SetClipSpaceNear(float near) { m_ClipNear = near; }
		void SetClipSpaceFar(float far) { m_ClipFar = far; }

		void ResizeView(float width, float height);
		void SetShaderMatrices(Ref<Shader> shader);

		static Camera* GetMain() { return s_Main; }
		static Vector2 WorldToScreenPoint(Vector3& pos);
	private:
		static Camera* s_Main;

		CameraMode m_CameraMode = CameraMode::Perspective;

		glm::mat4 m_View;
		glm::mat4 m_Projection;

		float m_OrthoSize;
		float m_FieldOfView;
		float m_AspectRatio;
		float m_ClipNear;
		float m_ClipFar;
	};
}