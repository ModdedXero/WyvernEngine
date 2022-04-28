#include "Wyvern.h"

#include <WyvernEditor/Utility/EditorGUI.h>

namespace Wyvern
{
	void Transform::DrawEditor()
	{
		Editor::EditorGUI::Vector3Control("Position", this->position);
		Editor::EditorGUI::Vector3Control("Rotation", this->rotation);
		Editor::EditorGUI::Vector3Control("Scale", this->scale, 1.0f);
	}

	void SpriteRenderer::DrawEditor()
	{
		Editor::EditorGUI::Color4Control("Color", this->color);
	}
}