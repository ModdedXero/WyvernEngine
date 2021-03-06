#pragma once

#include "Layer.h"
#include "LayerStack.h"

#include <Wyvern/Tools/FileSystem.h>
#include <Wyvern/Display/Window.h>
#include <Wyvern/Events/Event.h>
#include <Wyvern/Events/WindowEvent.h>
#include <Wyvern/ImGui/ImGuiLayer.h>

#include <chrono>

namespace Wyvern
{
	struct ApplicationSpecification
	{
		std::string Name = "Wyvern Engine";

		uint32_t WindowWidth = 1600;
		uint32_t WindowHeight = 900;
		bool StartMaximized = false;
		bool VSync = false;

		Tools::FileSystem AssetsPath = "./Project/Assets";
		Tools::FileSystem ResourcesPath = "./Project/Resources";
		Tools::FileSystem DefaultShader = ResourcesPath / "/Shader/StandardShader.glsl";
	};

	class Application
	{
	public:
		Application(const ApplicationSpecification& specification = ApplicationSpecification());
		~Application();

		virtual void Run();
		virtual void Close();

		virtual void OnEvent(Events::Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

		Display::Window& GetWindow() const { return *m_Window; }
		ImGuiLayer* GetImGuiLayer() const { return m_ImGuiLayer; }

		static Application& Get() { return *s_Instance; }
		static ApplicationSpecification GetSpecification() { return s_Instance->m_Specification; }

	private:
		static Application* s_Instance;

		ApplicationSpecification m_Specification;
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