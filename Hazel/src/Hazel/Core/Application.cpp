#include "hzpch.h"
#include "Application.h"
#include "Hazel/Core/Input.h"
#include "Hazel/Renderer/Renderer.h"

#include <GLFW/glfw3.h> // included for time move to platform

namespace Hazel {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;

	

	Application::Application()
	{
		HZ_PROFILE_FUNCTION();

		HZ_CORE_ASSERT(!s_Instance, "Application already exists");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));

		Renderer::Init();

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);
	}

	Application::~Application()
	{
		HZ_PROFILE_FUNCTION();

		Renderer::Shutdown();
	}

	void Application::PushLayer(Layer* layer)
	{
		HZ_PROFILE_FUNCTION();

		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* overlay)
	{
		HZ_PROFILE_FUNCTION();

		m_LayerStack.PushOverlay(overlay);
		overlay->OnAttach();
	}

	void Application::OnEvent(Event& event)
	{
		HZ_PROFILE_FUNCTION();

		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(OnWindowResize));
		

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
		{
			(*--it)->OnEvent(event);
			if (event.IsHandled())
				break;
		}
	}

	void Application::Run()
	{
		HZ_PROFILE_FUNCTION();
		
		while (m_Running)
		{
			HZ_PROFILE_SCOPE("RunLoop");

			float time = (float)glfwGetTime(); // TODO: Platform::GetTime
			Timestep timestep = time - m_LastFrameTime;
			m_LastFrameTime = time;
			
			// pause updating if window is minimized
			if (!m_Minimized)
			{
				{
					HZ_PROFILE_SCOPE("LayerStack OnUpdate");

					// update layerstack
					for (Layer* layer : m_LayerStack)
						layer->OnUpdate(timestep);
				}
			
				// update ImGUI
				// TODO: handle pausing and minimizing undocked ImGUI windows
				m_ImGuiLayer->Begin();
				{
					HZ_PROFILE_SCOPE("LayerStack OnImGuiRender");
					for (Layer* layer : m_LayerStack)
						layer->OnImGuiRender();
				}
				m_ImGuiLayer->End();

			}


			m_Window->OnUpdate();

			//Update();
		}
	}


	bool Application::OnWindowClose(WindowCloseEvent& event)
	{
		m_Running = false;
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& event)
	{
		HZ_PROFILE_FUNCTION();

		if (event.GetWidth() == 0 || event.GetHeight() == 0)
		{
			m_Minimized = true;
			return false;
		}
		m_Minimized = false;
		Renderer::OnWindowResize(event.GetWidth(), event.GetHeight());

		return false;
	}

}