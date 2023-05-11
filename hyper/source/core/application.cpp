#include "pch.h"

#include "hyper/core/application.h"

namespace hyper
{
	Application::Application(const char*)
	{

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
