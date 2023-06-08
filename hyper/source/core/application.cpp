#include "hyper/core/application.h"
#include "hyper/event/dispatcher.h"
#include "hyper/event/window_events.h"
#include "hyper/event/scene_events.h"
#include "hyper/scene/scene.h"
#include "hyper/service/service_hub.h"
#include "hyper/utils/clock.h"
#include "hyper/utils/assert.h"

#include <stdexcept>

#include "hyper/input/keyboard.h"

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
			m_pInput	= std::make_unique<Input>();

			m_pScene->AddObserver(this);
			m_pInput->AddObserver(this);
		}
		catch (const std::runtime_error& err)
		{
			LogError("Resource acquisition failed: {}", err.what());
			m_CanStart = false;
		}
	}

	void Application::Start()
	{
		if (m_CanStart)
		{
			m_IsRunning = true;

			Clock clock;
			float deltatime = 0.0f;

			while (m_IsRunning)
			{
				m_pInput->Update();
				m_pScene->Update(deltatime);

				m_pRenderer->BeginFrame();
				m_pScene->Render();
				m_pRenderer->EndFrame();

				deltatime = clock.Tick();
			}
		}
	}

	void Application::Stop()
	{
		m_IsRunning = false;
	}

	void Application::LoadScene(const std::function<void(Scene&, Input&)>& loadScene)
	{
		HyperAssert(loadScene != nullptr, "expected loadScene to be a valid function pointer");

		m_pInput->Reset();
		m_pScene->RemoveAllActors();

		loadScene(*m_pScene, *m_pInput);
	}

	bool Application::OnEvent(const AEvent& event)
	{
		Dispatcher dispatcher(event);

		dispatcher.Dispatch(&Application::OnWindowCloseEvent, this);
		dispatcher.Dispatch(&Application::OnSceneStopRequestEvent, this);
		dispatcher.Dispatch(&Application::OnSceneLoadRequestEvent, this);

		return dispatcher.IsEventHandled();
	}

	bool Application::OnWindowCloseEvent(const WindowCloseEvent& event)
	{
		if (event.id == m_pWindow->GetId())
		{
			Stop();
			return true;
		}
		return false;
	}

	bool Application::OnSceneStopRequestEvent(const SceneStopRequestEvent& event)
	{
		if (&event.scene == m_pScene.get())
		{
			Stop();
			return true;
		}
		return false;
	}

	bool Application::OnSceneLoadRequestEvent(const SceneLoadRequestEvent& event)
	{
		if (&event.scene == m_pScene.get())
		{
			LoadScene(event.loadScene);
			return true;
		}
		return false;
	}
}
