#pragma once

#include <Merlin/Core/Math/Math.h>

#include <Merlin/Renderer/Renderer2D.h>
#include <Merlin/Renderer/Shader.h>
#include <Merlin/Renderer/Texture2D.h>
#include <Merlin/Renderer/ResourceManager.h>

#include <Merlin/Core/Log.h>

namespace Merlin
{
	struct Transform
	{
		Vector3 position;
		Vector3 rotation;
		Vector3 scale = Vector3(1, 1, 1);
	};

	struct Material2D
	{
		void Render(Transform& transform)
		{
			if (shader < 0 || shader == UINT_MAX) return;

			if (texture < 0 || texture == UINT_MAX)
			{
				Renderer2D::DrawQuad(transform.position,
					transform.scale, this->color);
			}
			else
			{
				Renderer2D::DrawQuad(transform.position,
					transform.scale, ResourceManager::GetTexture("Default").ID);
			}
		}

		unsigned int shader = -1;
		unsigned int texture = -1;
		Vector4 color = { 1.0f, 1.0f, 1.0f, 1.0f };
	};
}