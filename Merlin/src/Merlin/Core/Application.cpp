#include "mlpch.h"
#include "Application.h"

#include "Timestep.h"

#include <Merlin/Core/Scene/Entity.h>
#include <Merlin/Renderer/Renderer2D.h>

#include <Merlin/Core/Scene/EntityWizard.h>
#include <Merlin/Core/Physics/Physics2DWizard.h>
#include <Merlin/Renderer/RenderWizard.h>
#include <Merlin/UI/UIWizard.h>

#include "ResourceManager.h"

#include <iostream>
#include <chrono>

using namespace Merlin::Events;
using namespace Merlin::Display;
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

		m_Window = Window::Create();
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));

		m_StartTime = Time::now();
		m_FixedLoop = Time::now();

		// Initialize Engine and Wizards
		Renderer2D::OnAwake();

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

		PushWizard(new EntityWizard());
		PushWizard(new Physics2DWizard());
		PushWizard(new RenderWizard());
		PushWizard(new UIWizard());

		// Initialize Default Assets
		ResourceManager::LoadShader("../merlin/assets/shader/standardshader.vert",
			"../merlin/assets/shader/standardshader.frag", nullptr, "StandardShader");
		ResourceManager::LoadShader("../merlin/assets/shader/fontshader.vert",
			"../merlin/assets/shader/fontshader.frag", nullptr, "FontShader");

		ResourceManager::LoadMaterial("StandardShader", "StandardMaterial");
		ResourceManager::LoadMaterial("FontShader", "StandardFontMaterial")->sortValue = 100;

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
		m_Running = true;

		while (m_Running)
		{
			m_Window->OnUpdate();

			Renderer2D::BeginScene();

			// All application logic
			// Get time since application start
			auto cTime = Time::now();
			fsec fs = cTime - m_StartTime;

			// Get Delta time for Layers
			fsec deltaTime = cTime - m_LastFrameTime;

			if (deltaTime.count() > 10.0f)
			{
				Timestep::m_Time = 0;
				Timestep::m_DeltaTime = 0;
			}
			else
			{
				Timestep::m_Time = fs.count();
				Timestep::m_DeltaTime = deltaTime.count();
			}

			m_LastFrameTime = cTime;

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

			for (Wizard* wizard : m_WizardStack)
				wizard->OnUpdate();

			fsec fixed = Time::now() - m_FixedLoop;
			if (fixed.count() > Constants::FixedUpdateInterval)
			{
				for (Layer* layer : m_LayerStack)
					layer->OnFixedUpdate();

				for (Wizard* wizard : m_WizardStack)
					wizard->OnFixedUpdate();

				m_FixedLoop = Time::now();
			}

			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
				layer->OnUIRender();
			m_ImGuiLayer->End();

			Renderer2D::EndScene();

			m_Window->OnRender();
		}
	}

	void Application::OnEvent(Events::Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Distpatch<WindowResizeEvent>(BIND_EVENT_FN(Application::OnWindowResize));

		for (Wizard* wizard : m_WizardStack)
		{
			if (e.Handled)
				break;
			wizard->OnEvent(e);
		}

		for (Layer* layer : m_LayerStack)
		{
			if (e.Handled)
				break;
			layer->OnEvent(e);
		}
	}

	void Application::Close()
	{
		m_Running = false;
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
			return true;
		}

		m_Minimized = false;
		glfwSetWindowSize(m_Window->GetNativeWindow(), m_Window->GetWidth(), m_Window->GetHeight());

		return true;
	}
}