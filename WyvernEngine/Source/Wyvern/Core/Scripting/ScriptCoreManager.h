#pragma once

#include <Wyvern/Utils/FileSystem.h>

namespace Wyvern
{
	class ScriptCoreMangager
	{
	public:
		static void GenerateScriptCore(Utils::FileSystem projectPath);
	};
}