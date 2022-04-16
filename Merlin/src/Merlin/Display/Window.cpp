#include "Window.h"

#include <Merlin/Events/KeyEvent.h>
#include <Merlin/Events/WindowEvent.h>
#include <Merlin/Events/MouseEvent.h>

namespace Merlin::Display
{
	Window::Window(const WindowProps& props)
	{
		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;

		// Check if GLFW is Initialized
		if (!glfwInit())
		{
			// Log Error
			return;
		}

		m_Window = glfwCreateWindow(props.Width, props.Height, props.Title, NULL, NULL);
		if (!m_Window)
		{
			// Log Error
			return;
		}

		glfwSetWindowAspectRatio(m_Window, 16, 9);

		glfwMakeContextCurrent(m_Window);
		gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		glfwSetWindowUserPointer(m_Window, &m_Data);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		// Create GLFW Callback Events
		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				switch (action)
				{
					case GLFW_PRESS:
					{
						Events::KeyPressedEvent pressEvent(key, 0);
						data.EventCallback(pressEvent);
						break;
					}
					case GLFW_REPEAT:
					{
						Events::KeyPressedEvent holdEvent(key, 1);
						data.EventCallback(holdEvent);
						break;
					}
				}
		});

		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				data.Width = width;
				data.Height = height;

				Events::WindowResizeEvent event(width, height);
				data.EventCallback(event);
		});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xpos, double ypos)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				Events::MouseMovedEvent event(xpos, ypos);
				data.EventCallback(event);
			});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				Events::MouseButtonPressedEvent event(button, action);
				data.EventCallback(event);
			});
	}

	void Window::OnUpdate()
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glfwPollEvents();
	}

	void Window::OnRender()
	{
		glfwSwapBuffers(m_Window);
	}

	void Window::OnDestory()
	{
		glfwTerminate();
	}

	Window* Window::Create(const WindowProps& props)
	{
		return new Window(props);
	}
}