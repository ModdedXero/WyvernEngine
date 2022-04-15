#include "EditorCamera.h"

namespace Merlin
{
	void EditorCamera::OnAttach()
	{
		AddComponent<Camera>();
		GetTransform()->position.z = 8;
	}

	void EditorCamera::OnUpdate(Timestep ts)
	{
		
	}

	void EditorCamera::OnEvent(Events::Event& e)
	{

	}
}