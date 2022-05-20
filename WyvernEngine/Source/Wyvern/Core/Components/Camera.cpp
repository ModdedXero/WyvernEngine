#include "wvpch.h"
#include "Camera.h"

#include <Wyvern/Core/Scene/EntityList.h>

namespace Wyvern
{
	Camera* Camera::GetActiveCamera()
	{
		for (Entity* ent : EntityList<Camera>(Scene::GetActiveScene()))
		{
			Camera* camera = Scene::GetComponent<Camera>(ent);
			if (camera->m_ActiveCamera)
				return camera;
		}

		return nullptr;
	}

	void Camera::SetActiveCamera(Camera* camera)
	{
		for (Entity* ent : EntityList<Camera>(Scene::GetActiveScene()))
		{
			Camera* camera = Scene::GetComponent<Camera>(ent);
			if (camera->m_ActiveCamera)
				camera->m_ActiveCamera = false;
		}

		if (camera) camera->m_ActiveCamera = true;
	}
}