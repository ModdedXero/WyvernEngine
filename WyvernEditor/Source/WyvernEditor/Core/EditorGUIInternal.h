#pragma once

#include <Wyvern/Utils/FileSystem.h>

namespace Wyvern::Editor
{
	class EditorGUIInternal
	{
	public:
		static Utils::FileSystem* DragDropTarget(const char* label, const char* id);
	};
}