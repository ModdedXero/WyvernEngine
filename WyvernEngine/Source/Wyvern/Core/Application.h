#pragma once

#include "Layer.h"
#include "LayerStack.h"

#include <Wyvern/Display/Window.h>

#include <Wyvern/Events/Event.h>
#include <Wyvern/Events/WindowEvent.h>

#include <Wyvern/Core/Scene/SceneSerializer.h>

#include <Wyvern/ImGui/ImGuiLayer.h>

#include <chrono>

namespace Wyvern
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
		ImGuiLayer* GetImGuiLayer() { return m_ImGuiLayer; }

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