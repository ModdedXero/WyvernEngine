#include "wvpch.h"
#include "Application.h"

#include "Timestep.h"

#include <Wyvern/Renderer/Renderer2D.h>
#include <Wyvern/Core/Physics/Physics2DWizard.h>
#include <Wyvern/Core/Scene/Scene.h>

#include <iostream>
#include <chrono>

using namespace Wyvern::Events;
using namespace Wyvern::Display;
using namespace Wyvern::Renderer;

namespace Wyvern
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

		Renderer2D::OnAwake();
		Scene::CreateWizard<Physics2DWizard>(); // Remove and automate later with settings window

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

		DEBUG_CORE("Wyvern Engine Started");
	}

	Application::~Application()
	{
		for (Layer* layer : m_LayerStack)
			layer->OnDetach();
	}

	void Application::Run()
	{
		m_Running = true;

		while (m_Running)
		{
			m_Window->OnUpdate();

			CalculateTimestep();

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

			fsec fixed = Time::now() - m_FixedLoop;
			if (fixed.count() > Constants::FixedUpdateInterval)
			{
				for (Layer* layer : m_LayerStack)
					layer->OnFixedUpdate();

				m_FixedLoop = Time::now();
			}

			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
				layer->OnUIRender();
			m_ImGuiLayer->End();

			m_Window->OnRender();
		}
	}

	void Application::Close()
	{
		m_Running = false;
	}

	void Application::OnEvent(Events::Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Distpatch<WindowResizeEvent>(BIND_EVENT_FN(Application::OnWindowResize));

		for (Layer* layer : m_LayerStack)
		{
			if (e.Handled)
				break;
			layer->OnEvent(e);
		}
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

	void Application::CalculateTimestep()
	{
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
	}
}