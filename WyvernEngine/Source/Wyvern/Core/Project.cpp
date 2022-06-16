#include "wvpch.h"
#include "Project.h"

#include <Wyvern/Core/Scene/Scene.h>
#include <Wyvern/Core/Scene/Serializer.h>
#include <Wyvern/Core/Application/Application.h>

#include <yaml-cpp/yaml.h>

namespace Wyvern
{
	Tools::FileSystem Project::s_StartScenePath;

	void Project::LoadProject(Tools::FileSystem& project)
	{
		YAML::Node in;

		in = YAML::Load(project.ReadFile());

		if (!in["Project"])
			return;

		s_StartScenePath = in["StartScene"].as<std::string>();
	}

	void Project::SaveProject()
	{
		Tools::FileSystem projectPath = Application::GetSpecification().AssetsPath / "/project.wproj";
		YAML::Emitter out;

		out << YAML::BeginMap;

		out << YAML::Key << "Project" << YAML::Value << "Project File";
		out << YAML::Key << "StartScene" << YAML::Value << s_StartScenePath;

		out << YAML::EndMap;

		projectPath.WriteFile(out.c_str());
	}

	Tools::FileSystem Project::GetAssetsPath()
	{
		return Application::GetSpecification().AssetsPath;
	}

	Tools::FileSystem Project::GetResourcesPath()
	{
		return Application::GetSpecification().ResourcesPath;
	}

	void Project::SetStartScene(Ref<Scene> scene)
	{
		s_StartScenePath = scene->m_ScenePath;
	}

	Ref<Scene> Project::LoadStartScene()
	{
		Ref<Scene> scene = CreateRef<Scene>();
		Scene::SetActiveScene(scene);
		Serializer::Deserialize(scene, s_StartScenePath);
		scene->OnAttach();
		return scene;
	}
}