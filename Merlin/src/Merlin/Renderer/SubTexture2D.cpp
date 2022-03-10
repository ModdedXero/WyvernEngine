#include "SubTexture2D.h"

namespace Merlin::Renderer
{
    SubTexture2D::SubTexture2D(Texture2D& texture, const Vector2& min, const Vector2& max)
        : m_Texture(texture)
    {
        m_TexCoords[0] = { min.x, min.y };
        m_TexCoords[1] = { max.x, min.y };
        m_TexCoords[2] = { max.x, max.y };
        m_TexCoords[3] = { min.x, max.y };
    }

    SubTexture2D SubTexture2D::CreateFromCoords(Texture2D& texture, const Vector2& coords, const Vector2& spriteSize)
    {
        Vector2 min = { (coords.x * spriteSize.x) / texture.Width, (coords.y * spriteSize.y) / texture.Height };
        Vector2 max = { ((coords.x + 1) * spriteSize.x) / texture.Width, ((coords.y + 1) * spriteSize.y) / texture.Height };
        return SubTexture2D(texture, min, max);
    }
}