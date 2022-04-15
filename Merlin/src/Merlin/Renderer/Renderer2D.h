#pragma once

#include <Merlin/Core/Graphics/Sprite.h>
#include <Merlin/Core/Graphics/Material.h>
#include <Merlin/Core/Scene/Transform.h>
#include <Merlin/Core/Math/Vector.h>

#include "Framebuffer.h"

namespace Merlin::Renderer
{
	class Renderer2D
	{
	public:
		static void OnAwake();
		static void OnDestroy();

		static void BeginScene();
		static void EndScene();

		static void DrawQuad(Transform* transform, Ref<Material> material, Ref<Sprite> sprite, const Vector4& color);
		static void DrawQuad(const Vector3& pos, const Vector2& size, const Vector4& color);
		static void DrawQuad(const Vector3& pos, const Vector2& size, Texture2D* texture);

		static void DrawText(Vector3 pos, const Vector2& size, const std::string& text);

		static Framebuffer* framebuffer;
	private:
		static void BeginBatch();
		static void EndBatch();
		static void Flush();
	};
}