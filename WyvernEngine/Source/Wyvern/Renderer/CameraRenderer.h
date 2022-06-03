#pragma once

#include <Wyvern/Core/Graphics/Shader.h>
#include <Wyvern/Core/Math/Math.h>

#include <glm/glm.hpp>

namespace Wyvern
{
	struct Transform;
}

namespace Wyvern::Render
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

		CameraMode GetCameraMode() const	{ return m_CameraMode; }
		float GetOrthoSize() const			{ return m_OrthoSize; }
		float GetFieldOfView() const		{ return m_FieldOfView; }
		float GetClipNear() const			{ return m_ClipNear; }
		float GetClipFar() const			{ return m_ClipFar; }
		glm::mat4 GetProjection() const		{ return m_Projection; }
		glm::mat4 GetView() const			{ return m_View; }
		Vector2 GetCameraSize() const		{ return m_CameraSize; }

		void SetCameraMode(CameraMode mode);
		void SetProjection(float width, float height);
		void SetOrthoSize(float orthoSize) { m_OrthoSize = orthoSize; }
		void SetFieldOfView(float fov) { m_FieldOfView = fov; }
		void SetClipNear(float near) { m_ClipNear = near; }
		void SetClipFar(float far) { m_ClipFar = far; }

		void Resize(float width, float height) { SetProjection(width, height); }
		void SetShaderMatrices(Shader shader, Transform* position);

		static Vector2 WorldToScreenPoint(Vector3& pos);
	private:
		void RecalculateProjection();

		CameraMode m_CameraMode = CameraMode::Orthographic;

		glm::mat4 m_View;
		glm::mat4 m_Projection;

		Vector2 m_CameraSize;

		float m_OrthoSize;
		float m_FieldOfView;
		float m_AspectRatio;
		float m_ClipNear;
		float m_ClipFar;
	};
}