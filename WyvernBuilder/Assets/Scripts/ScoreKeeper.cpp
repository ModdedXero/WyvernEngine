#include "ScoreKeeper.h"

#include <WyvernEditor.h>

using namespace Wyvern::Editor;

void ScoreKeeper::DrawEditor()
{
	EditorGUI::EntityControl("Score1", Score1);
	EditorGUI::EntityControl("Score2", Score2);
	EditorGUI::EntityControl("Score3", Score3);
}

void ScoreKeeper::OnCollision2D(const Wyvern::Collision2D& collision)
{
	if (collision.entB.GetTag()->name == std::string("Ball"))
	{
		if (Score1.IsValid())
			Score1.DestroyEntity();
		else if (Score2.IsValid())
			Score2.DestroyEntity();
		else if (Score3.IsValid())
		{
			Score3.DestroyEntity();
			Wyvern::Timestep::SetTimeScale(0.0f);
		}
	}
}