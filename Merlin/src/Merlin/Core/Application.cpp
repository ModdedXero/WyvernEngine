#include "mlpch.h"
#include "Application.h"

#include <Merlin/Scene/Entity.h>
#include <Merlin/Scene/Components.h>
#include <Merlin/Scene/ComponentList.h>

#include <Merlin/Renderer/Renderer2D.h>
#include <Merlin/Core/Timestep.h>

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

		Renderer2D::OnAwake();

		m_StartTime = Time::now();

		ML_LOG_INFO("Merlin Engine Started");
	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		while (m_Window->IsRunning())
		{
			m_Window->OnUpdate();

			// All application logic
			Renderer2D::BeginBatch();

			// Get time since application start
			auto cTime = Time::now();
			fsec fs = cTime - m_StartTime;

			// Get Delta time for Layers
			fsec deltaTime = cTime - m_LastFrameTime;

			Timestep ts = Timestep(fs.count(), deltaTime.count());
			m_LastFrameTime = cTime;

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate(ts);

			for (Entity* ent : ComponentList<Material2D>())
			{
				ent->GetComponent<Material2D>()->Render(*ent->GetTransform());
			}

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