#pragma once

#include "Texture2D.h"

#include <Wyvern/Core/Math/Vector.h>

namespace Wyvern
{
	class Sprite
	{
	public:
		Sprite();
		Sprite(Ref<Texture2D> texture, const Vector2& min, const Vector2& max);

		const Ref<Texture2D> GetTexture() const { return m_Texture; }
		const std::vector<Vector2> GetTexCoords() const { return m_TexCoords; }

		void SetTexture(Ref<Texture2D> texture) { m_Texture = texture; }
		void SetTexCoords(std::vector<Vector2> coords) { m_TexCoords = coords; }

		static Ref<Sprite> CreateFromCoords(Ref<Texture2D> texture, const Vector2& coords, const Vector2& tileSize, const Vector2& spriteSize);

	private:
		Ref<Texture2D> m_Texture;
		std::vector<Vector2> m_TexCoords;
	};
}