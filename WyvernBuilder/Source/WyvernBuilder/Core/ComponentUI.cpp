#include <Wyvern.h>
#include <WyvernEditor.h>

using namespace Wyvern::Editor;

namespace Wyvern
{
	void Tag::DrawEditor()
	{

	}

	void Transform::DrawEditor()
	{
		EditorGUI::Vector3Control("Position", this->position);
		EditorGUI::Vector3Control("Rotation", this->rotation);
		EditorGUI::Vector3Control("Scale", this->scale, 1.0f);
	}

	void Camera::DrawEditor()
	{
		int cameraMode = (int)GetCameraMode();
		const char* values[] = { "Perspective", "Orthographic" };
		bool isActive = IsActive();
		float orthoSize = GetOrthoSize();
		float fov = GetFieldOfView();
		float clipNear = GetClipNear();
		float clipFar = GetClipFar();

		EditorGUI::ComboControl("Mode", values, cameraMode, 2);
		EditorGUI::BoolControl("Active Camera", isActive);
		EditorGUI::Color4Control("Clear Color", clearColor);
		if ((Render::CameraMode)cameraMode == Render::CameraMode::Orthographic) 
			EditorGUI::FloatControl("Ortho Size", orthoSize);
		if ((Render::CameraMode)cameraMode == Render::CameraMode::Perspective) 
			EditorGUI::FloatControl("FOV", fov);
		EditorGUI::FloatControl("Near Clip", clipNear);
		EditorGUI::FloatControl("Far Clip", clipFar);

		SetCameraMode((Render::CameraMode)cameraMode);
		if (isActive) 
			SetActive();
		else 
			SetActiveCamera(nullptr);
		SetOrthoSize(orthoSize);
		SetFieldOfView(fov);
		SetClipNear(clipNear);
		SetClipFar(clipFar);
	}

	void SpriteRenderer::DrawEditor()
	{
		EditorGUI::Color4Control("Color", this->color);

		Tools::FileSystem target = (sprite && sprite->GetTexture()) ? sprite->GetTexture()->GetPath() : "";
		EditorGUI::FileSystemControl("Sprite", target);

		if (target.IsExtension(".png"))
		{
			if (sprite && sprite->GetTexture() && sprite->GetTexture()->GetPath() == target) return;

			sprite = Sprite::CreateFromCoords(Texture2D::Create(target), { 0,0 }, { 1,1 }, { 32,32 });
		}

		if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(0))
		{
			sprite = nullptr;
		}
	}

	void MeshRenderer::DrawEditor()
	{

	}

	void MeshFilter::DrawEditor()
	{

	}

	void RigidBody2D::DrawEditor()
	{
		EditorGUI::FloatControl("Mass", this->mass);
		EditorGUI::FloatControl("Drag", this->drag);
		EditorGUI::FloatControl("Bounce", this->bounce);
		
		int index = (int)bodyType;
		const char* values[] = { "Dynamic", "Kinematic", "Static" };

		EditorGUI::ComboControl("Body Type", values, index, 3);
		bodyType = (PhysicsBody)index;
	}

	void BoxCollider2D::DrawEditor()
	{
		EditorGUI::Vector2Control("Size", size);
	}

	void SphereCollider2D::DrawEditor()
	{
		EditorGUI::FloatControl("Radius", radius);
	}
}