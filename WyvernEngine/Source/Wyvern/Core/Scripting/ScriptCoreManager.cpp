#include "wvpch.h"
#include "ScriptCoreManager.h"

#include <Wyvern/Core/Application/Application.h>

namespace Wyvern
{
	void ScriptCoreManager::GenerateScriptCore()
	{
		ApplicationSpecification specs = Application::Get().GetSpecification();

		std::string premakeCommand;
		premakeCommand = std::string("call %WYVERN_DIR%\\vendor\\premake\\premake5.exe vs2022 --file=../Assets/NewProjectTemplate/premake5.lua ") + "--projname=" + specs.ProjectName + " --projdir=" + (std::string)specs.ProjectPath;

		system(premakeCommand.c_str());

		std::string assetsPath;
		assetsPath = std::string(specs.ProjectPath) + "\\" + specs.ProjectName + "\\Assets";
		Utils::FileSystem::CreateDirectory(assetsPath);

		DEBUG_CORE("Built Script Core Project ", specs.ProjectName);
	}

	void ScriptCoreManager::CreateNewScript(Utils::FileSystem path, Utils::FileSystem script)
	{
		std::string templateString = script.ReadFile();

		Utils::FileSystem headerPath = path;
		headerPath /= "NewScript.h";
		Utils::FileSystem cppPath = path;
		cppPath /= "NewScript.cpp";

		size_t hOffset = templateString.find("##HEADER##") + 11;
		size_t cOffset = templateString.find("##CPP##");

		std::string hString = templateString.substr(hOffset, cOffset - 11);
		std::string cString = templateString.substr(cOffset + 8);

		headerPath.WriteFile(hString);
		cppPath.WriteFile(cString);
	}
}