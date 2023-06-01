#if defined(HYPER_BACKEND_SDL2)
#	include "backend/sdl2/core/sdl2_window.h"
#endif

namespace hyper
{
	Window::Window(uint32_t width, uint32_t height, std::string_view title)
	{
		m_pImpl = new Impl(this, width, height, title);
	}

	Window::~Window()
	{
		delete m_pImpl;
	}

	void Window::Show()
	{
		m_pImpl->Show();
	}

	void Window::Hide()
	{
		m_pImpl->Hide();
	}

	void* Window::GetNativeWindow() const
	{
		return m_pImpl->GetNativeWindow();
	}
}
