#include "TestMovement.h"

void TestMovement::OnUpdate()
{
	if (Input::IsKey(KeyCode::W))
	{
		GetTransform()->position.y -= 3.0f * Timestep::GetDeltaTime();
	}
}

void TestMovement::DrawEditor()
{

}