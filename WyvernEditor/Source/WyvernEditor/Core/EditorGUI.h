#pragma once

#include <Wyvern/Core/Math/Vector.h>

namespace Wyvern::Editor
{
	class EditorGUI
	{
	public:
		static void Vector2Control(const std::string& label, Vector2& values, float resetValue = 0.0f, float columnWidth = 80.0f);
		static void Vector3Control(const std::string& label, Vector3& values, float resetValue = 0.0f, float columnWidth = 80.0f);
		static void Vector4Control(const std::string& label, Vector4& values, float resetValue = 0.0f, float columnWidth = 80.0f);

		static void Color4Control(const std::string& label, Vector4& values);

		static void FloatControl(const std::string& label, float& value, float columnWidth = 80.0f);
		static void IntControl(const std::string& label, int& value, float columnWidth = 80.0f);
	};
}