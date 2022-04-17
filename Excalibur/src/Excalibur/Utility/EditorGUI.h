#pragma once

#include <Merlin.h>

namespace Merlin::Editor
{
	class EditorGUI
	{
	public:
		static void Vector3Control(const std::string& label, Vector3& values, float resetValue = 0.0f, float columnWidth = 100.0f);
	};
}