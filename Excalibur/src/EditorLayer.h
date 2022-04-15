#pragma once
#include <Merlin.h>

#include "EditorCamera.h"

namespace Merlin
{
	class EditorLayer : public Layer
	{
	public:
		EditorLayer();
		virtual ~EditorLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		virtual void OnUpdate(Timestep ts) override;
		virtual void OnImGuiRender() override;
		virtual void OnEvent(Events::Event& e) override;
	private:
		EditorCamera* m_Camera;
		Ref<Renderer::Framebuffer> m_Framebuffer;
	};
}