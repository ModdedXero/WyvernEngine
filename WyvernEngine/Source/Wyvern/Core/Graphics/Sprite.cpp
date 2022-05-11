#include "wvpch.h"
#include "Sprite.h"

namespace Wyvern
{
    Sprite::Sprite()
    {

    }

    Sprite::Sprite(Ref<Texture2D> texture, const Vector2& min, const Vector2& max)
        : m_Texture(texture)
    {
        m_TexCoords.push_back({ min.x, min.y });
        m_TexCoords.push_back({ max.x, min.y });
        m_TexCoords.push_back({ max.x, max.y });
        m_TexCoords.push_back({ min.x, max.y });
    }

    Ref<Sprite> Sprite::CreateFromCoords(Ref<Texture2D> texture, const Vector2& coords, const Vector2& tileSize, const Vector2& spriteSize)
    {
        Vector2 min = { (coords.x * spriteSize.x * tileSize.x) / texture->GetWidth(), (coords.y * spriteSize.y * tileSize.y) / texture->GetHeight()};
        Vector2 max = { ((coords.x + 1) * spriteSize.x * tileSize.x) / texture->GetWidth(), ((coords.y + 1) * spriteSize.y * tileSize.y) / texture->GetHeight()};
        return CreateRef<Sprite>(texture, min, max);
    }
}