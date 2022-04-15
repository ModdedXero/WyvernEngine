#pragma once

#include "Layer.h"
#include "LayerStack.h"

#include <Merlin/Display/Window.h>

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

		void Close();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		void PushWizard(Wizard* wizard);

		virtual bool OnWindowResize(Events::WindowResizeEvent& e);

		Display::Window& GetWindow() { return *m_Window; }

		static Application& Get() { return *s_Instance; }
	private:
		static Application* s_Instance;

		Display::Window* m_Window;
		ImGuiLayer* m_ImGuiLayer;

		LayerStack m_LayerStack;
		WizardStack m_WizardStack;

		bool m_Minimized = false;
		bool m_Running = false;

		std::chrono::steady_clock::time_point m_LastFrameTime;
		std::chrono::steady_clock::time_point m_StartTime;

		std::chrono::steady_clock::time_point m_FixedLoop;
	};
}