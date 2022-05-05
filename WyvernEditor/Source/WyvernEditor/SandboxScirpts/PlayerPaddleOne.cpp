#include "PlayerPaddleOne.h"

#include "WyvernEditor/Utility/EditorGUI.h"

void PlayerPaddleOne::OnUpdate()
{
	if (altControls == 1)
	{
		if (Input::IsKey(KeyCode::Up))
		{
			GetTransform()->position.y += paddleSpeed * Timestep::GetDeltaTime();
		}

		if (Input::IsKey(KeyCode::Down))
		{
			GetTransform()->position.y -= paddleSpeed * Timestep::GetDeltaTime();
		}

		return;
	}

	if (Input::IsKey(KeyCode::W))
	{
		GetTransform()->position.y += paddleSpeed * Timestep::GetDeltaTime();
	}

	if (Input::IsKey(KeyCode::S))
	{
		GetTransform()->position.y -= paddleSpeed * Timestep::GetDeltaTime();
	}
}

void PlayerPaddleOne::DrawEditor()
{
	Editor::EditorGUI::FloatControl("Speed", paddleSpeed);
	Editor::EditorGUI::IntControl("Alt Control", altControls);
}