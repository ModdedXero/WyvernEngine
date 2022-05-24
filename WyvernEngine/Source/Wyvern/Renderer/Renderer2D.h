#pragma once

#include "Framebuffer.h"
#include "CameraRenderer.h"

#include <Wyvern/Core/Graphics/Sprite.h>
#include <Wyvern/Core/Graphics/Material.h>
#include <Wyvern/Core/Components/Transform.h>
#include <Wyvern/Core/Math/Vector.h>

namespace Wyvern::Renderer
{
	class Renderer2D
	{
	public:
		static void Intitialize();
		static void Destruct();

		static void BeginScene(CameraRenderer* cameraRenderer, Transform* cameraPosition, Vector4 clearColor = { 0.1f, 0.1f, 0.25f, 1.0f });
		static void EndScene();

		static void DrawQuad(Transform* transform, Ref<Material> material, Ref<Sprite> sprite, const Vector4& color, int entityID);
		static void DrawText(Vector3 pos, const Vector2& size, const std::string& text);

		static Ref<Framebuffer> GetFramebuffer() { return s_Framebuffer; }
	private:
		static void BeginBatch();
		static void EndBatch();
		static void Flush();

	private:
		static Ref<Framebuffer> s_Framebuffer;
	};
}