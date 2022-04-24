#pragma once

#include <Merlin/Core/Scene/Component.h>
#include <Merlin/Renderer/CameraRenderer.h>

namespace Merlin
{
	struct Camera : public Component
	{
		Renderer::CameraRenderer* GetRenderer() { return m_Renderer; }

	private:
		Renderer::CameraRenderer* m_Renderer = new Renderer::CameraRenderer();
	};
}