#include "mlpch.h"
#include "Application.h"

#include "Timestep.h"

#include <Merlin/Core/Scene/Entity.h>
#include <Merlin/Renderer/Renderer2D.h>
#include <Merlin/Core/Physics/Physics2DWizard.h>
#include <Merlin/Renderer/RenderWizard.h>
#include <Merlin/UI/UIWizard.h>

#include "ResourceManager.h"

#include <iostream>
#include <chrono>

using namespace Merlin::Events;
using namespace Merlin::Window;
using namespace Merlin::Renderer;
using namespace Merlin::UI;

namespace Merlin
{
	typedef std::chrono::high_resolution_clock Time;
	typedef std::chrono::duration<float> fsec;
	
	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		s_Instance = this;

		m_Window = Window::Window::Create();
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));

		m_StartTime = Time::now();
		m_FixedLoop = Time::now();

		// Initialize Engine and Wizards
		Renderer2D::OnAwake();
		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

		PushWizard(new Physics2DWizard());
		PushWizard(new RenderWizard());
		PushWizard(new UIWizard());

		// Initialize Default Assets
		ResourceManager::LoadShader("../merlin/assets/shader/standardshader.vert",
			"../merlin/assets/shader/standardshader.frag", nullptr, "StandardShader");
		ResourceManager::LoadShader("../merlin/assets/shader/fontshader.vert",
			"../merlin/assets/shader/fontshader.frag", nullptr, "FontShader");

		ResourceManager::LoadMaterial("StandardShader", "StandardMaterial");

		DEBUG_LOG("Merlin Engine Started");
	}

	Application::~Application()
	{
		for (Layer* layer : m_LayerStack)
			layer->OnDetach();

		for (Wizard* wizard : m_WizardStack)
			wizard->OnDetach();
	}

	void Application::Run()
	{
		while (m_Window->IsRunning())
		{
			m_Window->OnUpdate();

			Renderer2D::BeginScene();

			// All application logic
			// Get time since application start
			auto cTime = Time::now();
			fsec fs = cTime - m_StartTime;

			// Get Delta time for Layers
			fsec deltaTime = cTime - m_LastFrameTime;

			Timestep ts;
			if (deltaTime.count() > 10.0f)
				ts = Timestep(0, 0);
			else
				ts = Timestep(fs.count(), deltaTime.count());

			m_LastFrameTime = cTime;

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate(ts);

			for (Wizard* wizard : m_WizardStack)
				wizard->OnUpdate(ts);

			fsec fixed = Time::now() - m_FixedLoop;
			if (fixed.count() > Constants::FixedUpdateInterval)
			{
				for (Layer* layer : m_LayerStack)
					layer->OnFixedUpdate(ts);

				for (Wizard* wizard : m_WizardStack)
					wizard->OnFixedUpdate(ts);

				m_FixedLoop = Time::now();
			}

			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender();
			m_ImGuiLayer->End();

			Renderer2D::EndScene();

			m_Window->OnRender();
		}
	}

	void Application::OnEvent(Events::Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Distpatch<WindowResizeEvent>(BIND_EVENT_FN(Application::OnWindowResize));

		for (Layer* layer : m_LayerStack)
			layer->OnEvent(e);

		for (Wizard* wizard : m_WizardStack)
			wizard->OnEvent(e);
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* overlay)
	{
		m_LayerStack.PushOverlay(overlay);
		overlay->OnAttach();
	}

	void Application::PushWizard(Wizard* wizard)
	{
		m_WizardStack.PushWizard(wizard);
		wizard->OnAttach();
	}

	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		if (e.GetWidth() == 0 || e.GetHeight() == 0)
		{
			m_Minimized = true;
			return false;
		}

		m_Minimized = false;
		glfwSetWindowSize(m_Window->GetNativeWindow(), m_Window->GetWidth(), m_Window->GetHeight());
		glViewport(0, 0, m_Window->GetWidth(), m_Window->GetHeight());

		return true;
	}
}