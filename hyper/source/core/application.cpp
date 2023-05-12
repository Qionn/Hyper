#include "pch.h"

#include "hyper/core/application.h"
#include "hyper/service/service_hub.h"

namespace hyper
{
	Application::Application(const char* pName)
	{
		ServiceHub::register_service<ConsoleLogService>(pName);
	}

	void Application::start()
	{
		m_IsRunning = true;

		while (m_IsRunning)
		{

		}
	}

	void Application::stop()
	{
		m_IsRunning = false;
	}
}
