#ifndef __HYPER_SDL2_CONTEXT_H__
#define __HYPER_SDL2_CONTEXT_H__

#include <SDL.h>
	
#include "hyper/graphics/context.h"

namespace hyper
{
	class SDL2Context final : public IContext
	{
	public:
		SDL2Context(SDL_Renderer* pRenderer);

		void DrawTexture(const ITexture& texture, const Rectf& dstRect) const override;
		void DrawTexture(const ITexture& texture, const Recti& srcRect, const Rectf& dstRect) const override;

		std::unique_ptr<ITexture> CreateTexture(std::string_view filepath) override;
		std::unique_ptr<ITexture> CreateTexture(std::string_view fontFilepath, int ptSize, std::string_view text, const glm::vec3& color) override;

		SDL2Context(const SDL2Context&)				= delete;
		SDL2Context(SDL2Context&&)					= delete;
		SDL2Context& operator=(const SDL2Context&)	= delete;
		SDL2Context& operator=(SDL2Context&&)		= delete;

		~SDL2Context();

	private:
		SDL_Renderer* m_pRenderer;
	};
}

#endif // !__HYPER_SDL2_CONTEXT_H__
