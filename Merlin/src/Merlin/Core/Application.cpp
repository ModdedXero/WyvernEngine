#include "mlpch.h"
#include "Application.h"

#include <Merlin/Scene/Entity.h>
#include <Merlin/Scene/ComponentList.h>

#include <Merlin/Renderer/Renderer2D.h>
#include <Merlin/Core/Timestep.h>

#include <Merlin/Core/Physics/Physics2DWizard.h>
#include <Merlin/Renderer/RenderWizard.h>

#include <iostream>
#include <chrono>

using namespace Merlin::Events;

namespace Merlin
{
#define BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

	typedef std::chrono::high_resolution_clock Time;
	typedef std::chrono::duration<float> fsec;
	
	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		s_Instance = this;

		m_Window = Window::Create();
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));

		m_StartTime = Time::now();

		// Initialize Engine and Wizards
		Renderer2D::OnAwake();

		PushWizard(new RenderWizard());
		PushWizard(new Physics2DWizard());

		ML_LOG_INFO("Merlin Engine Started");
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

			Renderer2D::BeginBatch();

			// All application logic
			// Get time since application start
			auto cTime = Time::now();
			fsec fs = cTime - m_StartTime;

			// Get Delta time for Layers
			fsec deltaTime = cTime - m_LastFrameTime;

			Timestep ts = Timestep(fs.count(), deltaTime.count());
			m_LastFrameTime = cTime;

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate(ts);

			for (Wizard* wizard : m_WizardStack)
				wizard->OnUpdate(ts);

			Renderer2D::EndBatch();
			Renderer2D::Flush();

			m_Window->OnRender();
		}
	}

	void Application::OnEvent(Events::Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Distpatch<WindowResizeEvent>(BIND_EVENT_FN(Application::OnWindowResize));

		for (Layer* layer : m_LayerStack)
			layer->OnEvent(e);
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

		return false;
	}
}