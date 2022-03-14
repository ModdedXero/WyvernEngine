#pragma once

#include "Layer.h"
#include "LayerStack.h"

#include <Merlin/Window/Window.h>

#include <Merlin/Events/Event.h>
#include <Merlin/Events/WindowEvent.h>

#include <Merlin/Core/Scene/Wizard.h>
#include <Merlin/Core/Scene/WizardStack.h>

#include <Merlin/ImGui/ImGuiLayer.h>

#include <chrono>

namespace Merlin
{
	class Application
	{
	public:
		Application();
		~Application();

		virtual void Run();

		virtual void OnEvent(Events::Event& e);

		virtual void PushLayer(Layer* layer);
		virtual void PushOverlay(Layer* overlay);

		virtual void PushWizard(Wizard* wizard);

		virtual bool OnWindowResize(Events::WindowResizeEvent& e);

		Window::Window& GetWindow() { return *m_Window; }

		static Application& Get() { return *s_Instance; }
	private:
		static Application* s_Instance;

		Window::Window* m_Window;
		ImGuiLayer* m_ImGuiLayer;

		LayerStack m_LayerStack;
		WizardStack m_WizardStack;

		bool m_Minimized = false;

		std::chrono::steady_clock::time_point m_LastFrameTime;
		std::chrono::steady_clock::time_point m_StartTime;

		std::chrono::steady_clock::time_point m_FixedLoop;
	};
}