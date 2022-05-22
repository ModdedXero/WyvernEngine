#include "ScoreKeeper.h"

#include <WyvernEditor.h>

using namespace Wyvern::Editor;

void ScoreKeeper::DrawEditor()
{
	std::string targetName = Wyvern::Scene::IsEntityValid(Score) ? Score.GetTag()->name : "Select Entity";
	EditorGUIInternal::DragDropTarget(targetName.c_str(), DragDropTypes::Entity, Score);
}