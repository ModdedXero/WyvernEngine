#include "ScoreKeeper.h"

#include <WyvernEditor.h>

void ScoreKeeper::DrawEditor()
{
	ImGui::Button("Entity");

	if (ImGui::BeginDragDropTarget())
	{
		if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("ENTITY_LINK"))
		{
			Wyvern::Entity* entPtr = (Wyvern::Entity*)payload->Data;
			Score = *entPtr;
		}

		ImGui::EndDragDropTarget();
	}

	DEBUG_CORE(Wyvern::Scene::IsEntityValid(Score));
}