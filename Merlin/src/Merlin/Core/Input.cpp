#include "mlpch.h"
#include "Input.h"

#include <GLFW/glfw3.h>

namespace Merlin
{
	bool Input::IsKeyImpl(int keycode)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetKey(window, keycode);
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
		return false;
	}

	bool Input::IsMouseButtonUpImpl(int keycode)
	{
		return false;
	}

	bool Input::IsMouseButtonDownImpl(int keycode)
	{
		return false;
	}
}