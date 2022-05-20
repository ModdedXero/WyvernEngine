#include "wvpch.h"
#include "Camera.h"

#include <Wyvern/Core/Scene/EntityList.h>

namespace Wyvern
{
	Camera* Camera::GetActiveCamera()
	{
		Camera* cachedCamera = nullptr;

		for (Entity* ent : EntityList<Camera>(Scene::GetActiveScene()))
		{
			Camera* camera = Scene::GetComponent<Camera>(ent);

			if (!cachedCamera)
				cachedCamera = camera;

			if (camera->m_ActiveCamera)
				return camera;
		}

		if (cachedCamera) 
			cachedCamera->m_ActiveCamera = true;

		return cachedCamera;
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