#include "mlpch.h"
#include "RenderWizard.h"

#include "Material2D.h"
#include "Renderer2D.h"
#include "Camera.h"

namespace Merlin::Renderer
{
	void RenderWizard::OnUpdate(Timestep ts) const
	{
		for (Entity* ent : EntityList<Material2D>())
		{
			Material2D* mat = ent->GetComponent<Material2D>();

			if (mat->shader < 0 || mat->shader == UINT_MAX) return;

			if (mat->texture < 0 || mat->texture == UINT_MAX)
			{
				Renderer2D::DrawQuad(ent->GetTransform()->position,
					ent->GetTransform()->scale, mat->color);
			}
			else if (mat->subTexture != nullptr)
			{
				Renderer2D::DrawQuad(ent->GetTransform()->position,
					ent->GetTransform()->scale, *mat->subTexture);
			}
			else
			{
				Renderer2D::DrawQuad(ent->GetTransform()->position,
					ent->GetTransform()->scale, mat->texture);
			}
		}

		if (Camera::main == nullptr || Camera::main->transform == nullptr) return;

		Camera::main->RecalculateMatrix();
		Camera::main->SetShaderMatrix();
	}
}