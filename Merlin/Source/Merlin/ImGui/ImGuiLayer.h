#pragma once

#include <Merlin/Core/Layer.h>
#include <Merlin/Core/Timestep.h>

#include <Platform/OpenGL/ImGuiOpenGLRenderer.h>
#include <Platform/OpenGL/ImGuiGLFWRenderer.h>

namespace Merlin
{
	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnAttach() override;
		void OnDetach() override;

		void Begin();
		void End();

		void SetDarkThemeColors();
		ImGuiContext* GetImGuiContext() { return m_ImGuiContext; }
	private:
		ImGuiContext* m_ImGuiContext;
	};
}