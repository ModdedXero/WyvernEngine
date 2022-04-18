#pragma once

#include <Merlin.h>

namespace Merlin::Editor
{
	class EditorGUI
	{
	public:
		static void Vector3Control(const std::string& label, Vector3& values, float resetValue = 0.0f, float columnWidth = 80.0f);
		static void Vector4Control(const std::string& label, Vector4& values, float resetValue = 0.0f, float columnWidth = 80.0f);
	};
}