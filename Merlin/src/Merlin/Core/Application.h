#pragma once

#include <Merlin/Window/Window.h>
#include <Merlin/Core/Layer.h>
#include <Merlin/Core/LayerStack.h>

#include <Merlin/Core/Events/Event.h>
#include <Merlin/Core/Events/WindowEvent.h>

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

		virtual bool OnWindowResize(Events::WindowResizeEvent& e);

		Window& GetWindow() { return *m_Window; }

		static Application& Get() { return *s_Instance; }
	private:
		static Application* s_Instance;
		Window* m_Window;

		LayerStack m_LayerStack;

		bool m_Minimized = false;
	};
}