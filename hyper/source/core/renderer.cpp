#if defined(HYPER_PLATFORM_SDL2)
#	include "backend/sdl2/sdl2_renderer.h"
#endif

namespace hyper
{
	Renderer::Renderer(const Window& window)
	{
		m_pImpl = new Impl(window);
	}

	Renderer::~Renderer()
	{
		delete m_pImpl;
	}

	void Renderer::BeginFrame()
	{
		m_pImpl->BeginFrame();
	}

	void Renderer::EndFrame()
	{
		m_pImpl->EndFrame();
	}
}