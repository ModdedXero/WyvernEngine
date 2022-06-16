#pragma once

#include <Wyvern/Core/Base.h>
#include <Wyvern/Tools/FileSystem.h>

namespace Wyvern
{
	class Scene;

	class Project
	{
	public:
		static void LoadProject(Tools::FileSystem& project);
		static void SaveProject();

		static Tools::FileSystem GetAssetsPath();
		static Tools::FileSystem GetResourcesPath();

		static void SetStartScene(Ref<Scene> scene);
		static Ref<Scene> LoadStartScene();

	private:
		static Tools::FileSystem s_StartScenePath;
	};
}