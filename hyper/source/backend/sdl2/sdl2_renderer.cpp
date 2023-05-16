#include "sdl2_renderer.h"

#include "hyper/core/window.h"

#include <stdexcept>

namespace hyper
{
	Renderer::Impl::Impl(const Window& window)
	{
		auto pWindow = reinterpret_cast<SDL_Window*>(window.GetNativeWindow());

		m_pRenderer = SDL_CreateRenderer(pWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

		if (m_pRenderer == nullptr)
		{
			throw std::runtime_error("Failed to create SDL2 renderer");
		}
	}

	Renderer::Impl::~Impl()
	{
		SDL_DestroyRenderer(m_pRenderer);
	}

	void Renderer::Impl::BeginFrame()
	{
		SDL_RenderClear(m_pRenderer);
	}

	void Renderer::Impl::EndFrame()
	{
		SDL_RenderPresent(m_pRenderer);
	}
}
