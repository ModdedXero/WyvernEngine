#pragma once
#include <Wyvern.h>

#include <WyvernEditor.h>

#include <WyvernBuilder/Windows/ViewportWindow.h>
#include <WyvernBuilder/Windows/HierarchyWindow.h>
#include <WyvernBuilder/Windows/PropertiesWindow.h>
#include <WyvernBuilder/Windows/ContentBrowserWindow.h>

using namespace Wyvern::Editor;

namespace Wyvern
{
	class BuilderLayer : public Layer
	{
	public:
		virtual void OnAttach() override;
		virtual void OnDetach() override;

		virtual void OnUpdate() override;
		virtual void OnFixedUpdate() override;
		virtual void OnUIRender() override;
		virtual void OnEvent(Events::Event& e) override;

		static void OpenViewportWindow();
		static void OpenHierarchyWindow();
		static void OpenPropertiesWindow();
		static void OpenContentBrowserWindow();

		static ViewportCamera* GetViewportCamera() { return s_ViewportCamera; }

		static Entity* GetSelectedContext() { return s_SelectedContext; }
		static void SetSelectedContext(Entity* ent) { s_SelectedContext = ent; }

		static void SaveScene();
		static void LoadScene(std::string filePath);
	private:
		static Ref<Scene> s_ActiveScene;
		static Ref<Scene> s_CachedScene;
		static ViewportCamera* s_ViewportCamera;
		static Entity* s_SelectedContext;

		static ViewportWindow* s_ViewportWindow;
		static HierarchyWindow* s_HierarchyWindow;
		static PropertiesWindow* s_PropertiesWindow;
		static ContentBrowserWindow* s_ContentBrowserWindow;

		static std::vector<EditorWindow*> s_Windows;

		static void LoadSceneDialog();
		static void SetActiveScene(Ref<Scene> scene);
	};
}