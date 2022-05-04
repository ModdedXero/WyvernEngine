#include "EditorLayer.h"

#include <WyvernEditor/Utility/EditorGUI.h>

#include "imgui.h"

namespace Wyvern::Editor
{
    Ref<Scene> EditorLayer::s_ActiveScene;
    ViewportCamera* EditorLayer::s_EditorCamera = nullptr;
    Entity* EditorLayer::s_SelectedContext = nullptr;

    ViewportWindow* EditorLayer::s_ViewportWindow = nullptr;
    HierarchyWindow* EditorLayer::s_HierarchyWindow = nullptr;
    PropertiesWindow* EditorLayer::s_PropertiesWindow = nullptr;

    std::vector<EditorWindow*> EditorLayer::s_Windows;

	void EditorLayer::OnAttach()
	{
        s_ActiveScene = CreateRef<Scene>();
        Scene::SetActiveScene(s_ActiveScene);

        s_ActiveScene->CreateWizard<Physics2DWizard>();

        s_ActiveScene->OnAwake();
        ImGui::SetCurrentContext(Application::Get().GetImGuiLayer()->GetImGuiContext());

        s_EditorCamera = new ViewportCamera();

        OpenViewportWindow();
        OpenHierarchyWindow();
        OpenPropertiesWindow();
	}

	void EditorLayer::OnDetach()
	{
        for (EditorWindow* window : s_Windows)
            delete window;

        s_ActiveScene->OnDestroy();
	}

	void EditorLayer::OnUpdate()
	{
        for (EditorWindow* window : s_Windows)
        {
            window->OnPreRender();
        }

        s_ActiveScene->OnRuntimeUpdate();
        s_ActiveScene->OnEditorUpdate(s_EditorCamera, s_EditorCamera->transform->GetTransform());
        Scene::FlushScene();

        for (EditorWindow* window : s_Windows)
        {
            window->OnPostRender();
        }
	}

    void EditorLayer::OnFixedUpdate()
    {
        s_ActiveScene->OnFixedUpdate();
    }

	void EditorLayer::OnUIRender()
	{
        static bool dockspaceOpen = true;
        static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

        ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
        const ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->WorkPos);
        ImGui::SetNextWindowSize(viewport->WorkSize);
        ImGui::SetNextWindowViewport(viewport->ID);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
        window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

        // Begin Editor
        ImGui::Begin("DockSpace", &dockspaceOpen, window_flags);

        ImGui::PopStyleVar();
        ImGui::PopStyleVar(2);

        ImGuiIO& io = ImGui::GetIO();
        ImGuiStyle& style = ImGui::GetStyle();
        float minWinSize = style.WindowMinSize.x;
        style.WindowMinSize.x = 340.0f;
        if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
        {
            ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
            ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
        }

        style.WindowMinSize.x = minWinSize;

        if (ImGui::BeginMenuBar())
        {
            if (ImGui::BeginMenu("File"))
            {
                if (ImGui::MenuItem("New", "Ctrl+N"))
                {
                    s_ActiveScene->OnDestroy();
                }

                if (ImGui::MenuItem("Open...", "Ctrl+O"))
                {
                    std::string filePath = FileDialogs::OpenFile("Wyvern Scene (*.wyvern)\0*.wyvern\0");
                    if (!filePath.empty())
                    {
                        s_ActiveScene->OnDestroy();
                        Serializer::Deserialize(s_ActiveScene, filePath);
                    }
                }

                if (ImGui::MenuItem("Save As...", "Ctrl+Shift+S"))
                {
                    std::string filePath = FileDialogs::SaveFile("Wyvern Scene (*.wyvern)\0*.wyvern\0", "wyvern");
                    if (!filePath.empty())
                    {
                        Serializer::Serialize(Serializer::Serialize(s_ActiveScene), filePath);
                    }
                }

                if (ImGui::MenuItem("Exit")) 
                    Application::Get().Close();
                    
                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("Scene"))
            {
                if (ImGui::MenuItem(s_ActiveScene->GetSceneState() == SceneState::Edit ? "Play" : "Stop"))
                {
                    if (s_ActiveScene->GetSceneState() == SceneState::Edit)
                        s_ActiveScene->SetSceneState(SceneState::Play);
                    else
                        s_ActiveScene->SetSceneState(SceneState::Edit);
                }

                ImGui::EndMenu();
            }

            ImGui::EndMenuBar();
        }

        for (EditorWindow* window : s_Windows)
        {
            window->BeginRender();
            window->OnGUI();
            window->EndRender();
        }

        ImGui::End();
	}

	void EditorLayer::OnEvent(Events::Event& e)
	{
        for (EditorWindow* window : s_Windows)
        {
            if (window->IsFocused() && window->IsHovered())
                window->OnEvent(e);
        }

        s_ActiveScene->OnEvent(e);
	}

    void EditorLayer::OpenViewportWindow()
    {
        if (s_ViewportWindow == nullptr)
        {
            s_ViewportWindow = new ViewportWindow();
            s_ViewportWindow->OnAttach();
            s_Windows.push_back(s_ViewportWindow);
        }
    }

    void EditorLayer::OpenHierarchyWindow()
    {
        if (s_HierarchyWindow == nullptr)
        {
            s_HierarchyWindow = new HierarchyWindow();
            s_HierarchyWindow->OnAttach();
            s_Windows.push_back(s_HierarchyWindow);
        }
    }

    void EditorLayer::OpenPropertiesWindow()
    {
        if (s_PropertiesWindow == nullptr)
        {
            s_PropertiesWindow = new PropertiesWindow();
            s_PropertiesWindow->OnAttach();
            s_Windows.push_back(s_PropertiesWindow);
        }
    }
}