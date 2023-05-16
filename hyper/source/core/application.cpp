#include "hyper/core/application.h"
#include "hyper/core/time.h"
#include "hyper/event/dispatcher.h"
#include "hyper/event/window_events.h"
#include "hyper/service/service_hub.h"
#include "hyper/utils/logging.h"

#include <stdexcept>

namespace hyper
{
	Application::Application(std::string_view name)
	{
		ServiceHub::RegisterService<ConsoleLogService>(name);
		ServiceHub::RegisterService<DefaultSoundService>();

		try
		{
			m_pWindow = std::make_unique<Window>(800, 600, name);
			m_pRenderer = std::make_unique<Renderer>(*m_pWindow);
			m_pLayerStack = std::make_unique<LayerStack>();
		}
		catch (const std::runtime_error& err)
		{
			LogError("Application initialization failed: {}", err.what());
			std::exit(-1);
		}

		m_pWindow->AddObserver(this);
	}

	Application::~Application()
	{
		m_pWindow->RemoveObserver(this);
	}

	void Application::Start()
	{
		m_IsRunning = true;

		while (m_IsRunning)
		{
			Time::Start();

			m_pWindow->Update();

			m_pRenderer->BeginFrame();
			m_pLayerStack->Render();
			m_pRenderer->EndFrame();

			Time::Stop();
		}
	}

	void Application::Stop()
	{
		m_IsRunning = false;
	}

	void Application::PopLayer()
	{
		m_pLayerStack->Pop();
	}

	bool Application::OnEvent(const AEvent& event)
	{
		Dispatcher dispatcher(event);

		dispatcher.Dispatch(&Application::OnWindowCloseEvent, this);

		return dispatcher.IsEventHandled();
	}

	bool Application::OnWindowCloseEvent(const WindowCloseEvent&)
	{
		Stop();
		return true;
	}
}
