#include "EditorLayer.h"

#include "imgui.h"

namespace Merlin::Editor
{
    ViewportWindow* EditorLayer::m_ViewportWindow = nullptr;
    HierarchyWindow* EditorLayer::m_HierarchyWindow = nullptr;
    PropertiesWindow* EditorLayer::m_PropertiesWindow = nullptr;

    std::vector<EditorWindow*> EditorLayer::m_Windows;

    Entity* EditorLayer::m_SelectedContext = nullptr;

	EditorLayer::EditorLayer()
	{

	}

	void EditorLayer::OnAttach()
	{
        OpenViewportWindow();
        OpenHierarchyWindow();
        OpenPropertiesWindow();

		Entity* test = Scene::CreateEntity<Entity>();

		test->GetTransform()->position = { 0, 0, 0 };
		test->GetTransform()->scale = { 0.5f, 0.5f, 1.0f };
		SpriteRenderer* testRend = test->AddComponent<SpriteRenderer>();
		testRend->material = ResourceManager::GetMaterial("StandardMaterial");
        testRend->color = { 1.0f, 0.5f, 0.6f, 1.0f };

        Entity* test2 = Scene::CreateEntity<Entity>();

        test2->GetTransform()->position = { 2, 0, 0 };
        test2->GetTransform()->scale = { 0.5f, 0.5f, 1.0f };
        SpriteRenderer* testRend2 = test2->AddComponent<SpriteRenderer>();
        testRend2->material = ResourceManager::GetMaterial("StandardMaterial");
        testRend2->color = { 0.3f, 0.5f, 0.6f, 1.0f };

        test->AddChildEntity(test2);
        test->AddComponent<Camera>();
	}

	void EditorLayer::OnDetach()
	{
        for (EditorWindow* window : m_Windows)
            delete window;
	}

	void EditorLayer::OnUpdate()
	{

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
        ImGui::Begin("DockSpace Demo", &dockspaceOpen, window_flags);

        ImGui::PopStyleVar();
        ImGui::PopStyleVar(2);

        ImGuiIO& io = ImGui::GetIO();
        if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
        {
            ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
            ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
        }

        if (ImGui::BeginMenuBar())
        {
            if (ImGui::BeginMenu("File"))
            {
                if (ImGui::MenuItem("Exit")) Application::Get().Close();
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
            {
                window->OnEvent(e);
            }
        }
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