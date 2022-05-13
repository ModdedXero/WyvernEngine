#include "PongBall.h"

#include <WyvernEditor.h>

void PongBall::DrawEditor()
{
	Editor::EditorGUI::Vector2Control("Initial Force", initialForce);
}

void PongBall::OnAttach()
{
	RigidBody2D* rb = Scene::GetComponent<RigidBody2D>(GetEntity());
	rb->force = initialForce;
}