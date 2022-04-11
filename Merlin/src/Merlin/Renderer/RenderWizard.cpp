#include "mlpch.h"
#include "RenderWizard.h"

#include "Camera.h"
#include "Renderer2D.h"

#include <Merlin/Core/Graphics/Material.h>
#include <Merlin/Core/ResourceManager.h>

namespace Merlin::Renderer
{
	void RenderWizard::OnUpdate(Timestep ts)
	{
		for (Entity* ent : EntityList<Material>())
		{
			Material* mat = ent->GetComponent<Material>();

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