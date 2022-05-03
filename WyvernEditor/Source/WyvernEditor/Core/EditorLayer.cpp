#include "EditorLayer.h"

#include "imgui.h"

namespace Wyvern::Editor
{
    ViewportWindow* EditorLayer::m_ViewportWindow = nullptr;
    HierarchyWindow* EditorLayer::m_HierarchyWindow = nullptr;
    PropertiesWindow* EditorLayer::m_PropertiesWindow = nullptr;

    std::vector<EditorWindow*> EditorLayer::m_Windows;

    Entity* EditorLayer::m_SelectedContext = nullptr;
    ViewportCamera* EditorLayer::m_EditorCamera = nullptr;

    void TestNativeComponent::OnUpdate()
    {
        DEBUG_LOG("TEST adaddad");
    }

    void Test2NativeComponent::OnUpdate()
    {
        DEBUG_LOG("TEST opjokopkpo");
    }

	void EditorLayer::OnAttach()
	{
        OpenViewportWindow();
        OpenHierarchyWindow();
        OpenPropertiesWindow();

        Scene::OnAwake();
        ImGui::SetCurrentContext(Application::Get().GetImGuiLayer()->GetImGuiContext());

        m_EditorCamera = new ViewportCamera();
	}

	void EditorLayer::OnDetach()
	{
        for (EditorWindow* window : m_Windows)
            delete window;

        Scene::OnDestroy();
	}

	void EditorLayer::OnUpdate()
	{
        Scene::OnRuntimeUpdate();
        Scene::OnEditorUpdate(m_EditorCamera, m_EditorCamera->transform->GetTransform());
        Scene::FlushScene();
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
                    Scene::OnDestroy();
                }

                if (ImGui::MenuItem("Open...", "Ctrl+O"))
                {
                    std::string filePath = FileDialogs::OpenFile("Wyvern Scene (*.wyvern)\0*.wyvern\0");
                    if (!filePath.empty())
                    {
                        Scene::OnDestroy();
                        SceneSerializer::Deserialize(filePath);
                    }
                }

                if (ImGui::MenuItem("Save As...", "Ctrl+Shift+S"))
                {
                    std::string filePath = FileDialogs::SaveFile("Wyvern Scene (*.wyvern)\0*.wyvern\0", "wyvern");
                    if (!filePath.empty())
                    {
                        SceneSerializer::Serialize(filePath);
                    }
                }

                if (ImGui::MenuItem("Exit")) 
                    Application::Get().Close();
                    
                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("Scene"))
            {
                if (ImGui::MenuItem(Scene::GetSceneState() == SceneState::Edit ? "Play" : "Stop"))
                {
                    if (Scene::GetSceneState() == SceneState::Edit)
                        Scene::SetSceneState(SceneState::Play);
                    else
                        Scene::SetSceneState(SceneState::Edit);
                }

                ImGui::EndMenu();
            }

            ImGui::EndMenuBar();
        }

        for (EditorWindow* window : m_Windows)
        {
            window->BeginRender();
            window->OnGUI();
            window->EndRender();
        }

        ImGui::End();
	}

	void EditorLayer::OnEvent(Events::Event& e)
	{
        for (EditorWindow* window : m_Windows)
        {
            if (window->IsFocused() && window->IsHovered())
                window->OnEvent(e);
        }

        Scene::OnEvent(e);
	}

    void EditorLayer::OpenViewportWindow()
    {
        if (m_ViewportWindow == nullptr)
        {
            m_ViewportWindow = new ViewportWindow();
            m_Windows.push_back(m_ViewportWindow);
        }
    }

    void EditorLayer::OpenHierarchyWindow()
    {
        if (m_HierarchyWindow == nullptr)
        {
            m_HierarchyWindow = new HierarchyWindow();
            m_Windows.push_back(m_HierarchyWindow);
        }
    }

    void EditorLayer::OpenPropertiesWindow()
    {
        if (m_PropertiesWindow == nullptr)
        {
            m_PropertiesWindow = new PropertiesWindow();
            m_Windows.push_back(m_PropertiesWindow);
        }
    }
}