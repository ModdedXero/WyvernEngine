#pragma once

#include "Texture2D.h"
#include "SubTexture2D.h"

#include <Merlin/Core/Math/Vector.h>

namespace Merlin::Renderer
{
	class Renderer2D
	{
	public:
		static void OnAwake();
		static void OnDestroy();

		static void BeginBatch();
		static void EndBatch();
		static void Flush();

		static void DrawQuad(const Vector3& pos, const Vector2& size, const Vector4& color);
		static void DrawQuad(const Vector3& pos, const Vector2& size, Texture2D* texture);
		static void DrawQuad(const Vector3& pos, const Vector2& size, SubTexture2D* subTexture);
	};
}