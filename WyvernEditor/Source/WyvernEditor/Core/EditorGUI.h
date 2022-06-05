#pragma once

#include <Wyvern/Core/Math/Vector.h>
#include <Wyvern/Core/Scene/Entity.h>

namespace Wyvern::Editor
{
	const float DefaultColumnWidth = 50.0f;
	const float DefaultResetValue = 0.0f;

	class EditorGUI
	{
	public:
		static void Label(const std::string& label);

	public:
		static void Vector2Control(const std::string& label, Vector2& values, float resetValue = DefaultResetValue, float columnWidth = DefaultColumnWidth);
		static void Vector3Control(const std::string& label, Vector3& values, float resetValue = DefaultResetValue, float columnWidth = DefaultColumnWidth);
		static void Vector4Control(const std::string& label, Vector4& values, float resetValue = DefaultResetValue, float columnWidth = DefaultColumnWidth);

		static void Color4Control(const std::string& label, Vector4& values, float columnWidth = DefaultColumnWidth);

		static void FloatControl(const std::string& label, float& value, float columnWidth = DefaultColumnWidth);
		static void IntControl(const std::string& label, int& value, float columnWidth = DefaultColumnWidth);
		static void BoolControl(const std::string& label, bool& value, float columnWidth = DefaultColumnWidth);
		static void TextControl(const std::string& label, std::string& value, bool readOnly = false, float columnWidth = DefaultColumnWidth);
		
		static void ComboControl(const std::string& label, const char* values[], int& valueIndex, int arraySize, float columnWidth = DefaultColumnWidth);

		static void EntityControl(const std::string& label, Entity& entity, float columnWidth = DefaultColumnWidth);
		static void FileSystemControl(const std::string& label, Tools::FileSystem& file, float columnWidth = DefaultColumnWidth);
	};
}