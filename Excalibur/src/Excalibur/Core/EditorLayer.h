#pragma once
#include <Merlin.h>

#include "EditorWindow.h"

namespace Merlin
{
	class EditorLayer : public Layer
	{
	public:
		EditorLayer();
		virtual ~EditorLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		virtual void OnUpdate() override;
		virtual void OnUIRender() override;
		virtual void OnEvent(Events::Event& e) override;
	private:
		std::vector<EditorWindow*> m_Windows;
	};
}