#pragma once
#include <Wyvern.h>

#include "EditorWindow.h"

#include <WyvernEditor/Windows/ViewportWindow.h>
#include <WyvernEditor/Windows/HierarchyWindow.h>
#include <WyvernEditor/Windows/PropertiesWindow.h>

namespace Wyvern::Editor
{
	class EditorLayer : public Layer
	{
	public:
		virtual void OnAttach() override;
		virtual void OnDetach() override;

		virtual void OnUpdate() override;
		virtual void OnUIRender() override;
		virtual void OnEvent(Events::Event& e) override;

		static void OpenViewportWindow();
		static void OpenHierarchyWindow();
		static void OpenPropertiesWindow();

		static ViewportCamera* GetEditorCamera() { return s_EditorCamera; }
		static Ref<Scene> GetActiveScene() { return s_ActiveScene; }

		static Entity* GetSelectedContext() { return s_SelectedContext; }
		static void SetSelectedContext(Entity* ent) { s_SelectedContext = ent; }

	private:
		static Ref<Scene> s_ActiveScene;
		static ViewportCamera* s_EditorCamera;
		static Entity* s_SelectedContext;

		static ViewportWindow* s_ViewportWindow;
		static HierarchyWindow* s_HierarchyWindow;
		static PropertiesWindow* s_PropertiesWindow;

		static std::vector<EditorWindow*> s_Windows;
	};

	struct TestNativeComponent : public NativeScriptComponent
	{
		void OnUpdate() override;

		int awesomeLevel = 1;
	};

	struct Test2NativeComponent : public NativeScriptComponent
	{
		void OnUpdate() override;
	};
}