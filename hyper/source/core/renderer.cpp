#if defined(HYPER_BACKEND_SDL2)
#	include "backend/sdl2/core/sdl2_renderer.h"
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

	IContext& Renderer::GetContext() const
	{
		return m_pImpl->GetContext();
	}
}
