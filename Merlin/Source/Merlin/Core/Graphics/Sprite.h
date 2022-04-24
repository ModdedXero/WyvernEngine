#pragma once

#include <Merlin/Core/Base.h>
#include "Texture2D.h"

#include <Merlin/Core/Math/Vector.h>

namespace Merlin
{
	class Sprite
	{
	public:
		Sprite();
		Sprite(Ref<Texture2D> texture, const Vector2& min, const Vector2& max);

		const Ref<Texture2D> GetTexture() const { return m_Texture; }
		const Vector2* GetTexCoords() const { return m_TexCoords; }

		static Ref<Sprite> CreateFromCoords(Ref<Texture2D> texture, const Vector2& coords, const Vector2& tileSize, const Vector2& spriteSize);
	private:
		Ref<Texture2D> m_Texture;
		Vector2 m_TexCoords[4];
	};
}