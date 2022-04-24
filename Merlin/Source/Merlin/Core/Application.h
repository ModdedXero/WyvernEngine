#pragma once

#include "Layer.h"
#include "LayerStack.h"

#include <Merlin/Display/Window.h>

#include <Merlin/Events/Event.h>
#include <Merlin/Events/WindowEvent.h>

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
		virtual void Close();

		virtual void OnEvent(Events::Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		Display::Window& GetWindow() { return *m_Window; }

		static Application& Get() { return *s_Instance; }
	private:
		static Application* s_Instance;

		Display::Window* m_Window;

		ImGuiLayer* m_ImGuiLayer;
		
		bool OnWindowResize(Events::WindowResizeEvent& e);

		LayerStack m_LayerStack;

		bool m_Minimized = false;
		bool m_Running = false;

		void CalculateTimestep();

		std::chrono::steady_clock::time_point m_LastFrameTime;
		std::chrono::steady_clock::time_point m_StartTime;

		std::chrono::steady_clock::time_point m_FixedLoop;
	};
}