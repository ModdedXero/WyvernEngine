#include "mlpch.h"
#include "RenderWizard.h"

#include "Renderer2D.h"

#include <Merlin/Core/Graphics/SpriteRenderer.h>
#include <Merlin/Core/ResourceManager.h>

namespace Merlin::Renderer
{
	void RenderWizard::OnUpdate()
	{
		for (Entity* ent : EntityList<SpriteRenderer>())
		{
			SpriteRenderer* sRend = ent->GetComponent<SpriteRenderer>();

			if (sRend->material == nullptr || sRend->sprite == nullptr)
			{
				Renderer2D::DrawQuad(ent->GetTransform()->position, ent->GetTransform()->scale, sRend->color);
			}
			else
			{
				Renderer2D::DrawQuad(ent->GetTransform(), sRend->material, sRend->sprite, sRend->color);
			}
		}
	}
}