#include "sdl2_window.h"

#include "hyper/event/window_events.h"

#include <stdexcept>

namespace hyper
{
	Window::Impl::Impl(uint32_t width, uint32_t height, std::string_view title)
	{
		if (s_InstanceCount++ == 0)
		{
			if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
			{
				throw std::runtime_error("Failed to initialize the SDL2 library");
			}
		}

		m_pWindow = SDL_CreateWindow(title.data(),
									 SDL_WINDOWPOS_CENTERED,
									 SDL_WINDOWPOS_CENTERED,
									 static_cast<int>(width),
									 static_cast<int>(height),
									 SDL_WINDOW_SHOWN);

		if (m_pWindow == nullptr)
		{
			throw std::runtime_error("Failed to create the SDL2 window");
		}

		m_Id = SDL_GetWindowID(m_pWindow);
	}

	Window::Impl::~Impl()
	{
		SDL_DestroyWindow(m_pWindow);

		if (--s_InstanceCount == 0)
		{
			SDL_Quit();
		}
	}

	void Window::Impl::Update()
	{
		SDL_SetEventFilter(&Impl::EventFilter, &m_Id);

		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_WINDOWEVENT)
			{
				switch (event.window.event)
				{
					case SDL_WINDOWEVENT_CLOSE:
					{
						WindowCloseEvent e;
						FireEvent(e);
						break;
					}
				}
			}
		}
	}

	void Window::Impl::Show()
	{
		SDL_ShowWindow(m_pWindow);
	}

	void Window::Impl::Hide()
	{
		SDL_HideWindow(m_pWindow);
	}

	void* Window::Impl::GetNativeWindow() const
	{
		return m_pWindow;
	}

	void Window::Impl::SetEventCallback(const EventCallback& callback)
	{
		m_Callback = callback;
	}

	void Window::Impl::FireEvent(const AEvent& event) const
	{
		if (m_Callback != nullptr)
		{
			m_Callback(event);
		}
	}

	int Window::Impl::EventFilter(void* pUserData, SDL_Event* pEvent)
	{
		uint32_t windowId = *reinterpret_cast<uint32_t*>(pUserData);

		switch (pEvent->type)
		{
			case SDL_WINDOWEVENT:
				return pEvent->window.windowID == windowId;
		}

		return 0;
	}
}
