#ifndef __HYPER_SDL2_RENDERER_H__
#define __HYPER_SDL2_RENDERER_H__

#include <memory>

#include <SDL.h>

#include "hyper/core/renderer.h"

#include "sdl2_context.h"

namespace hyper
{
	class Renderer::Impl final
	{
	public:
		Impl(const Window& window);

		void BeginFrame();
		void EndFrame();

		IContext& GetContext() const;

		Impl(const Impl&)				= delete;
		Impl(Impl&&)					= delete;
		Impl& operator=(const Impl&)	= delete;
		Impl& operator=(Impl&&)			= delete;

		~Impl();

	private:
		SDL_Renderer* m_pRenderer;
		std::unique_ptr<IContext> m_pContext;
	};
}

#endif // !__HYPER_SDL2_RENDERER_H__
