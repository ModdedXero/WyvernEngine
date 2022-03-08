#pragma once

#include "Application.h"
#include "KeyCodes.h"

namespace Merlin
{
	class Input
	{
	public:
		static bool IsKey(int keycode)					{ return IsKeyImpl(keycode); }
		static bool IsKey(KeyCode keycode)				{ return IsKeyImpl((int)keycode); }
																 
		static bool IsKeyUp(int keycode)				{ return IsKeyUpImpl(keycode); }
		static bool IsKeyUp(KeyCode keycode)			{ return IsKeyUpImpl((int)keycode); }
																 
		static bool IsKeyDown(int keycode)				{ return IsKeyDownImpl(keycode); }
		static bool IsKeyDown(KeyCode keycode)			{ return IsKeyDownImpl((int)keycode); }
																 
		static bool IsMouseButton(int keycode)			{ return IsMouseButtonImpl(keycode); }
		static bool IsMouseButton(KeyCode keycode)		{ return IsMouseButtonImpl((int)keycode); }

		static bool IsMouseButtonUp(int keycode)		{ return IsMouseButtonUpImpl(keycode); }
		static bool IsMouseButtonUp(KeyCode keycode)	{ return IsMouseButtonUpImpl((int)keycode); }

		static bool IsMouseButtonDown(int keycode)		{ return IsMouseButtonDownImpl(keycode); }
		static bool IsMouseButtonDown(KeyCode keycode)	{ return IsMouseButtonDownImpl((int)keycode); }
	protected:
		static bool IsKeyImpl(int keycode);
		static bool IsKeyUpImpl(int keycode);
		static bool IsKeyDownImpl(int keycode);

		static bool IsMouseButtonImpl(int keycode);
		static bool IsMouseButtonUpImpl(int keycode);
		static bool IsMouseButtonDownImpl(int keycode);
	};
}