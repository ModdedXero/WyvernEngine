#include "ScoreKeeper.h"

#include <WyvernEditor.h>

using namespace Wyvern::Editor;

void ScoreKeeper::DrawEditor()
{
	EditorGUI::EntityControl("Score", Score);
}