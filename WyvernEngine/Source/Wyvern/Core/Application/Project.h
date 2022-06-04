#pragma once

#include <Wyvern/Core/Base.h>
#include <Wyvern/Tools/FileSystem.h>

namespace Wyvern
{
	class Scene;

	class Project
	{
	public:
		static void LoadProject();
		static void SaveProject();

		static void SetStartScene(Ref<Scene> scene);
		static Ref<Scene> LoadStartScene();

	private:
		static Tools::FileSystem s_StartScenePath;
	};
}