#include "Wyvern.h"

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

	}

	void SpriteRenderer::DrawEditor()
	{
		EditorGUI::Color4Control("Color", this->color);
	}

	void RigidBody2D::DrawEditor()
	{
		EditorGUI::FloatControl("Mass", this->mass);
		EditorGUI::FloatControl("Drag", this->drag);
		EditorGUI::FloatControl("Bounce", this->bounce);
		EditorGUI::IntControl("BodyType", this->m_BodyType);

		bodyType = (PhysicsBody)m_BodyType;
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