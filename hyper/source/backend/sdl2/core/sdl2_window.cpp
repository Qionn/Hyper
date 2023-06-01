#include "sdl2_window.h"

#include "hyper/event/window_events.h"

#include <backends/imgui_impl_sdl2.h>

#include <stdexcept>

namespace hyper
{
	Window::Impl::Impl(Window* pWindow, uint32_t width, uint32_t height, std::string_view title)
	{
		if (s_InstanceCount++ == 0)
		{
			if (SDL_InitSubSystem(SDL_INIT_VIDEO) < 0)
			{
				throw std::runtime_error("Failed to initialize SDL2 video subsystem");
			}
		}

		m_pWindow = SDL_CreateWindow(title.data(),
									 SDL_WINDOWPOS_CENTERED,
									 SDL_WINDOWPOS_CENTERED,
									 static_cast<int>(width),
									 static_cast<int>(height),
									 SDL_WINDOW_ALLOW_HIGHDPI);

		if (m_pWindow == nullptr)
		{
			throw std::runtime_error("Failed to create SDL2 window");
		}

		SDL_SetWindowData(m_pWindow, "hyper_window", pWindow);
	}

	Window::Impl::~Impl()
	{
		SDL_DestroyWindow(m_pWindow);

		if (--s_InstanceCount == 0)
		{
			SDL_QuitSubSystem(SDL_INIT_VIDEO);
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
}
