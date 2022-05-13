#include "wvpch.h"
#include "ScriptCoreManager.h"

#include <Wyvern/Core/Application/Application.h>

namespace Wyvern
{
	void ScriptCoreMangager::GenerateScriptCore(Utils::FileSystem projectPath)
	{
		ApplicationSpecification specs = Application::Get().GetSpecification();

		std::string premakeCommand;
		premakeCommand = std::string("call %WYVERN_DIR%\\vendor\\premake\\premake5.exe vs2022 --file=../Assets/NewProjectTemplate/premake5.lua ") + "--projname=" + specs.ProjectName + " --projdir=" + (std::string)specs.ProjectPath;

		system(premakeCommand.c_str());

		std::string assetsPath;
		assetsPath = std::string(specs.ProjectPath) + "\\" + specs.ProjectName + "\\Assets";
		Utils::FileSystem::CreateDirectory(assetsPath);
	}
}