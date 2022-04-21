#include "mlpch.h"
#include "RenderWizard.h"

#include "Renderer2D.h"

#include <Merlin/Core/Graphics/SpriteRenderer.h>

namespace Merlin::Renderer
{
	void RenderWizard::OnUpdate()
	{
		for (Entity* ent : EntityList<SpriteRenderer>())
		{
			SpriteRenderer* sRend = ent->GetComponent<SpriteRenderer>();

			Renderer2D::DrawQuad(ent->GetTransform(), sRend->material, sRend->sprite, sRend->color);
		}
	}
}