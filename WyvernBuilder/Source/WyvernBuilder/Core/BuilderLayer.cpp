#include "BuilderLayer.h"

#include "imgui.h"

namespace Wyvern
{
    Ref<Scene> BuilderLayer::s_ActiveScene;
    Ref<Scene> BuilderLayer::s_CachedScene;
    ViewportCamera* BuilderLayer::s_ViewportCamera = nullptr;
    Object* BuilderLayer::s_SelectedContext = nullptr;

    ViewportWindow* BuilderLayer::s_ViewportWindow = nullptr;
    HierarchyWindow* BuilderLayer::s_HierarchyWindow = nullptr;
    PropertiesWindow* BuilderLayer::s_PropertiesWindow = nullptr;
    ContentBrowserWindow* BuilderLayer::s_ContentBrowserWindow = nullptr;

    std::vector<EditorWindow*> BuilderLayer::s_Windows;

	void BuilderLayer::OnAttach()
	{
        SetActiveScene(Project::LoadStartScene());

#ifdef WV_DEBUG
        ImGui::SetCurrentContext(Application::Get().GetImGuiLayer()->GetImGuiContext());

        s_ViewportCamera = new ViewportCamera();

        OpenViewportWindow();
        OpenHierarchyWindow();
        OpenPropertiesWindow();
        OpenContentBrowserWindow();
#endif
	}

	void BuilderLayer::OnDetach()
	{
        for (EditorWindow* window : s_Windows)
            delete window;

        s_ActiveScene->OnDestroy();
	}

	void BuilderLayer::OnUpdate()
	{
        s_ActiveScene->OnRuntimeUpdate();
        if (s_ViewportCamera) s_ActiveScene->OnEditorUpdate(s_ViewportCamera, s_ViewportCamera->transform);

        Scene::FlushScene();
	}

    void BuilderLayer::OnFixedUpdate()
    {
        s_ActiveScene->OnFixedUpdate();
    }

	void BuilderLayer::OnUIRender()
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
        style.WindowMinSize.x = 280.0f;
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
                if (ImGui::MenuItem("Open...", "Ctrl+O"))
                {
                    LoadSceneDialog();
                }

                if (ImGui::MenuItem("Save"))
                {
                    Serializer::Serialize(Serializer::Serialize(s_ActiveScene), s_ActiveScene->GetScenePath());
                }

                if (ImGui::MenuItem("Save As...", "Ctrl+Shift+S"))
                {
                    SaveScene();
                }

                if (ImGui::MenuItem("Exit"))
                {
                    Project::SaveProject();
                    Application::Get().Close();
                }
                    
                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("Scene"))
            {
                if (ImGui::MenuItem(s_ActiveScene->GetSceneState() == SceneState::Edit ? "Play" : "Stop"))
                {
                    if (s_ActiveScene->GetSceneState() == SceneState::Edit)
                    {
                        Ref<Scene> runtimeScene = CreateRef<Scene>();
                        SerializeInfo& info = Serializer::Serialize(s_ActiveScene);
                        Serializer::ConvertSerialToDeserial(info);
                        s_CachedScene = s_ActiveScene;
                        SetActiveScene(runtimeScene);
                        Serializer::Deserialize(runtimeScene, info);
                        runtimeScene->SetSceneState(SceneState::Play);
                        runtimeScene->OnAttach();
                    }
                    else
                    {
                        s_ActiveScene->OnDestroy();
                        SetActiveScene(s_CachedScene);
                        s_ActiveScene->SetSceneState(SceneState::Edit);
                        s_ActiveScene->OnAttach();
                    }
                }

                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("Project"))
            {
                if (ImGui::MenuItem("Set Start Scene"))
                {
                    if (s_ActiveScene->GetSceneState() == SceneState::Edit)
                        Project::SetStartScene(s_ActiveScene);
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

	void BuilderLayer::OnEvent(Events::Event& e)
	{
        for (EditorWindow* window : s_Windows)
        {
            if (window->IsFocused() && window->IsHovered())
                window->OnEvent(e);
        }

        s_ActiveScene->OnEvent(e);
	}

    void BuilderLayer::OpenViewportWindow()
    {
        if (s_ViewportWindow == nullptr)
        {
            s_ViewportWindow = new ViewportWindow();
            s_ViewportWindow->OnAttach();
            s_Windows.push_back(s_ViewportWindow);
        }
    }

    void BuilderLayer::OpenHierarchyWindow()
    {
        if (s_HierarchyWindow == nullptr)
        {
            s_HierarchyWindow = new HierarchyWindow();
            s_HierarchyWindow->OnAttach();
            s_Windows.push_back(s_HierarchyWindow);
        }
    }

    void BuilderLayer::OpenPropertiesWindow()
    {
        if (s_PropertiesWindow == nullptr)
        {
            s_PropertiesWindow = new PropertiesWindow();
            s_PropertiesWindow->OnAttach();
            s_Windows.push_back(s_PropertiesWindow);
        }
    }

    void BuilderLayer::OpenContentBrowserWindow()
    {
        if (s_ContentBrowserWindow == nullptr)
        {
            s_ContentBrowserWindow = new ContentBrowserWindow();
            s_ContentBrowserWindow->OnAttach();
            s_Windows.push_back(s_ContentBrowserWindow);
        }
    }

    void BuilderLayer::SaveScene()
    {
        std::string filePath = FileDialogs::SaveFile("Wyvern Scene (*.wyvern)\0*.wyvern\0", "wyvern");
        if (!filePath.empty())
        {
            Serializer::Serialize(Serializer::Serialize(s_ActiveScene), filePath);
        }
    }

    void BuilderLayer::LoadScene(Tools::FileSystem filePath)
    {
        Ref<Scene> loadScene = CreateRef<Scene>();
        Serializer::Deserialize(loadScene, filePath);
        s_ActiveScene->OnDestroy();
        SetActiveScene(loadScene);
    }

    void BuilderLayer::LoadSceneDialog()
    {
        std::string filePath = FileDialogs::OpenFile("Wyvern Scene (*.wyvern)\0*.wyvern\0");
        if (!filePath.empty())
        {
            LoadScene(filePath);
        }
    }

    void BuilderLayer::SetActiveScene(Ref<Scene> scene)
    {
        SetSelectedContext(nullptr);
        s_ActiveScene = scene;
        Scene::SetActiveScene(scene);
    }
}