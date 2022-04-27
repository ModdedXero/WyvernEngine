#pragma once

#include <Merlin/Core/Components/Transform.h>

#include <Merlin/Core/Graphics/Shader.h>

#include <glm/glm.hpp>

namespace Merlin::Renderer
{
	enum class CameraMode
	{
		Perspective,
		Orthographic
	};

	struct CameraRenderer
	{
		CameraRenderer();
		~CameraRenderer() {}

		CameraMode GetCameraMode() { return m_CameraMode; }
		float GetOrthoSize() { return m_OrthoSize; }
		float GetFieldOfView() { return m_FieldOfView; }
		float GetClipNear() { return m_ClipNear; }
		float GetClipFar() { return m_ClipFar; }
		glm::mat4 GetProjection() { return m_Projection; }
		glm::mat4 GetView() { return m_View; }

		void SetCameraMode(CameraMode mode);
		void SetProjection(float width, float height);
		void SetOrthoSize(float orthoSize) { m_OrthoSize = orthoSize; }
		void SetFieldOfView(float fov) { m_FieldOfView = fov; }
		void SetClipSpaceNear(float near) { m_ClipNear = near; }
		void SetClipSpaceFar(float far) { m_ClipFar = far; }

		void ResizeView(float width, float height);
		void SetShaderMatrices(Ref<Shader> shader, const Matrix4x4& position);

		static CameraRenderer* GetActive() { return s_Active; }
		static void SetActiveCamera(CameraRenderer* camera) { s_Active = camera; }
		static Vector2 WorldToScreenPoint(Vector3& pos);
	private:
		static CameraRenderer* s_Active;

		void RecalculateProjection();

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