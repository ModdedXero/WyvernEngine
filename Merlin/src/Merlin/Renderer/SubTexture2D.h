#pragma once

#include "Texture2D.h"

#include <Merlin/Core/Math/Vector.h>

namespace Merlin::Renderer
{
	class SubTexture2D
	{
	public:
		SubTexture2D();
		SubTexture2D(Texture2D* texture, const Vector2& min, const Vector2& max);

		const Texture2D* GetTexture() const { return m_Texture; }
		const Vector2* GetTexCoords() const { return m_TexCoords; }

		static SubTexture2D* CreateFromCoords(Texture2D* texture, const Vector2& coords, const Vector2& spriteSize);
	private:
		Texture2D* m_Texture;
		Vector2 m_TexCoords[4];
	};
}