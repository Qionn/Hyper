#include "hyper/core/application.h"
#include "hyper/core/time.h"
#include "hyper/event/dispatcher.h"
#include "hyper/event/window_events.h"
#include "hyper/input/input.h"
#include "hyper/scene/scene.h"
#include "hyper/service/service_hub.h"
#include "hyper/utils/logging.h"

#include <stdexcept>

namespace hyper
{
	Application::Application(const Info& info)
	{
		ServiceHub::RegisterService<ConsoleLogService>(info.name);
		ServiceHub::RegisterService<DefaultSoundService>();

		try
		{
			m_pWindow	= std::make_unique<Window>(info.windowWidth, info.windowHeight, info.name);
			m_pRenderer	= std::make_unique<Renderer>(*m_pWindow);
			m_pScene	= std::make_unique<Scene>(m_pRenderer->GetContext());

			info.loadScene(*m_pScene);
		}
		catch (const std::runtime_error& err)
		{
			LogError("Application initialization failed: {}", err.what());
			std::exit(-1);
		}

		HYPER_INPUT.AddObserver(this);
	}

	Application::~Application()
	{
		HYPER_INPUT.RemoveObserver(this);
	}

	void Application::Start()
	{
		m_IsRunning = true;

		Input& input = HYPER_INPUT;

		while (m_IsRunning)
		{
			Time::Start();

			input.Update();
			m_pScene->Update(Time::DeltaTime());

			m_pRenderer->BeginFrame();
			m_pScene->Render();
			m_pRenderer->EndFrame();

			Time::Stop();
		}
	}

	void Application::Stop()
	{
		m_IsRunning = false;
	}

	bool Application::OnEvent(const AEvent& event)
	{
		Dispatcher dispatcher(event);

		dispatcher.Dispatch(&Application::OnWindowCloseEvent, this);

		return dispatcher.IsEventHandled();
	}

	bool Application::OnWindowCloseEvent(const WindowCloseEvent& event)
	{
		if (event.pWindow == m_pWindow.get())
		{
			Stop();
			return true;
		}
		return false;
	}
}
