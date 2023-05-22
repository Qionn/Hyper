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

		void DrawTexture(const ITexture& texture, const glm::vec2& pos) const override;
		void DrawTexture(const ITexture& texture, const glm::vec2& pos, float width, float height) const override;
		void DrawTexture(const ITexture& texture, float x, float y) const override;
		void DrawTexture(const ITexture& texture, float x, float y, float width, float height) const override;

		std::unique_ptr<ITexture> CreateTexture(std::string_view filepath) override;

		SDL2Context(const SDL2Context&)				= delete;
		SDL2Context(SDL2Context&&)					= delete;
		SDL2Context& operator=(const SDL2Context&)	= delete;
		SDL2Context& operator=(SDL2Context&&)		= delete;

		~SDL2Context() = default;

	private:
		SDL_Renderer* m_pRenderer;
	};
}

#endif // !__HYPER_SDL2_CONTEXT_H__
