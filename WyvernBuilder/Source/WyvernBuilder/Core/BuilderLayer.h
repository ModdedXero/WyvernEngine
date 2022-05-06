#pragma once
#include <Wyvern.h>

#include <WyvernEditor.h>

#include <WyvernBuilder/Windows/ViewportWindow.h>
#include <WyvernBuilder/Windows/HierarchyWindow.h>
#include <WyvernBuilder/Windows/PropertiesWindow.h>

namespace Wyvern::Editor
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

		static ViewportCamera* GetEditorCamera() { return s_EditorCamera; }

		static Entity* GetSelectedContext() { return s_SelectedContext; }
		static void SetSelectedContext(Entity* ent) { s_SelectedContext = ent; }

	private:
		static Ref<Scene> s_ActiveScene;
		static Ref<Scene> s_CachedScene;
		static ViewportCamera* s_EditorCamera;
		static Entity* s_SelectedContext;

		static ViewportWindow* s_ViewportWindow;
		static HierarchyWindow* s_HierarchyWindow;
		static PropertiesWindow* s_PropertiesWindow;

		static std::vector<EditorWindow*> s_Windows;

		static void SaveScene();
		static void LoadScene();
		static void SetActiveScene(Ref<Scene> scene);
	};
}