#pragma once

#include <Merlin/Events/Event.h>

#include <glad.h>
#include <GLFW/glfw3.h>

#include <string>

namespace Merlin::Window
{
	struct WindowProps
	{
		const char* Title;
		unsigned int Width = 0;
		unsigned int Height = 0;

		WindowProps(const char* title = "Merlin Engine",
			unsigned int width = 1280,
			unsigned int height = 720)
			: Title(title), Width(width), Height(height)
		{
		}
	};

	class Window
	{
		using EventCallbackFn = std::function<void(Events::Event&)>;
	public:
		void OnUpdate();
		void OnRender();
		void OnDestory();

		bool IsRunning() { return !glfwWindowShouldClose(m_Window); }
		void SetEventCallback(const EventCallbackFn& callback) { m_Data.EventCallback = callback; }

		unsigned int GetWidth() { return m_Data.Width; }
		unsigned int GetHeight() { return m_Data.Height; }

		GLFWwindow* GetNativeWindow() { return m_Window; }

		static Window* Create(const WindowProps& props = WindowProps());
	private:
		Window(const WindowProps& props);

		GLFWwindow* m_Window;

		struct WindowData
		{
			std::string Title;
			unsigned int Width, Height;

			EventCallbackFn EventCallback;
		};

		WindowData m_Data;
	};
}