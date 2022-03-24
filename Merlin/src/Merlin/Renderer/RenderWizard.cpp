#include "mlpch.h"
#include "RenderWizard.h"

#include "Material2D.h"
#include "Renderer2D.h"
#include "Camera.h"
#include "ResourceManager.h"

namespace Merlin::Renderer
{
	void RenderWizard::OnUpdate(Timestep ts)
	{
		for (Entity* ent : EntityList<Material2D>())
		{
			Material2D* mat = ent->GetComponent<Material2D>();

			if (mat->shader == nullptr) return;

			if (mat->texture != nullptr)
			{
				Renderer2D::DrawQuad(ent->GetTransform()->position,
					ent->GetTransform()->scale, mat->texture);
			}
			else if (mat->subTexture != nullptr)
			{
				Renderer2D::DrawQuad(ent->GetTransform()->position,
					ent->GetTransform()->scale, mat->subTexture);
			}
			else
			{
				Renderer2D::DrawQuad(ent->GetTransform()->position,
					ent->GetTransform()->scale, mat->color);
			}
		}

		if (Camera::GetMain() != nullptr)
			Camera::GetMain()->SetShaderMatrices();
	}
}