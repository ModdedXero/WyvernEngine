#pragma once

#include <Wyvern/Core/Scene/Component.h>
#include <Wyvern/Renderer/CameraRenderer.h>

namespace Wyvern
{
	struct Camera : public Component
	{
		Renderer::CameraRenderer* GetRenderer() { return m_Renderer; }

		WV_SERIALIZE_COMPONENT(Camera)
		WV_SERIALIZE_COMPONENT_END

	private:
		Renderer::CameraRenderer* m_Renderer = new Renderer::CameraRenderer();
	};
}