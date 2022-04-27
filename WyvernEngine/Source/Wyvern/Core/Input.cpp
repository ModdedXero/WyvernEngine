#include "wvpch.h"
#include "Input.h"

#include "Application.h"

#include <GLFW/glfw3.h>

namespace Wyvern
{
	bool Input::IsKeyImpl(int keycode)
	{
		GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		int state = glfwGetKey(window, keycode);
		return state == GLFW_PRESS;
	}

	bool Input::IsKeyUpImpl(int keycode)
	{
		return false;
	}
	bool Input::IsKeyDownImpl(int keycode)
	{
		return false;
	}

	bool Input::IsMouseButtonImpl(int keycode)
	{
		GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		int state = glfwGetMouseButton(window, keycode);
		return state == GLFW_PRESS;
	}

	bool Input::IsMouseButtonUpImpl(int keycode)
	{
		return false;
	}

	bool Input::IsMouseButtonDownImpl(int keycode)
	{
		return false;
	}

	Vector2 Input::MousePositionImpl()
	{
		double xpos, ypos;

		GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		glfwGetCursorPos(window, &xpos, &ypos);

		return Vector2(xpos, ypos);
	}
}