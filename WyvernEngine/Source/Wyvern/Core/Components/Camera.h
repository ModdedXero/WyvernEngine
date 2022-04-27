#pragma once

#include <Wyvern/Core/Scene/Component.h>
#include <Wyvern/Renderer/CameraRenderer.h>

namespace Wyvern
{
	struct Camera : public Component
	{
		Renderer::CameraRenderer* GetRenderer() { return m_Renderer; }

	private:
		Renderer::CameraRenderer* m_Renderer = new Renderer::CameraRenderer();
	};
}