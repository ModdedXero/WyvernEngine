#include "RenderWizard.h"

#include <Merlin/Renderer/Material2D.h>
#include <Merlin/Renderer/Renderer2D.h>
#include <Merlin/Renderer/Camera.h>

namespace Merlin
{
	void RenderWizard::OnUpdate(Timestep ts) const
	{
		for (Entity* ent : ComponentList<Material2D>())
		{
			Material2D* mat = ent->GetComponent<Material2D>();

			if (mat->shader < 0 || mat->shader == UINT_MAX) return;

			if (mat->texture < 0 || mat->texture == UINT_MAX)
			{
				Renderer2D::DrawQuad(ent->GetTransform()->position,
					ent->GetTransform()->scale, mat->color);
			}
			else
			{
				Renderer2D::DrawQuad(ent->GetTransform()->position,
					ent->GetTransform()->scale, mat->texture);
			}
		}

		Camera::Main().RecalculateMatrix();
		Camera::Main().SetShaderMatrix();
	}
}