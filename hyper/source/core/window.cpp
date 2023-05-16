#if defined(HYPER_PLATFORM_SDL2)
#	include "backend/sdl2/sdl2_window.h"
#endif

namespace hyper
{
	Window::Window(uint32_t width, uint32_t height, std::string_view title)
	{
		m_pImpl = new Impl(width, height, title);
		m_pImpl->SetEventCallback(std::bind(&Window::NotifyObservers, this, std::placeholders::_1));
	}

	Window::~Window()
	{
		delete m_pImpl;
	}

	void Window::Update()
	{
		m_pImpl->Update();
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
