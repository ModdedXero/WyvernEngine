#pragma once

#include <Wyvern/Utils/FileSystem.h>

namespace Wyvern
{
	class ScriptCoreManager
	{
	public:
		static void GenerateScriptCore();
		static void CreateNewScript(Utils::FileSystem path, Utils::FileSystem script);
	};
}