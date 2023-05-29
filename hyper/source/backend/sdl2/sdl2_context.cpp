#include "sdl2_context.h"
#include "sdl2_texture.h"

namespace hyper
{
	SDL2Context::SDL2Context(SDL_Renderer* pRenderer)
		: m_pRenderer{ pRenderer }
	{

	}

	void SDL2Context::DrawTexture(const ITexture& texture, const Rectf& dstRect) const
	{
		Recti srcRect = {
			.x		= 0,
			.y		= 0,
			.width	= texture.GetWidth(),
			.height	= texture.GetHeight()
		};

		DrawTexture(texture, srcRect, dstRect);
	}

	void SDL2Context::DrawTexture(const ITexture& texture, const Recti& srcRect, const Rectf& dstRect) const
	{
		const auto& sdl2Texture = reinterpret_cast<const SDL2Texture&>(texture);

		SDL_Rect sdlSrcRect = {
			.x = srcRect.x,
			.y = srcRect.y,
			.w = srcRect.width,
			.h = srcRect.height,
		};

		SDL_FRect sdlDstRect = {
			.x = dstRect.x,
			.y = dstRect.y,
			.w = dstRect.width,
			.h = dstRect.height
		};

		SDL_RenderCopyF(m_pRenderer, sdl2Texture.GetSDLTexture(), &sdlSrcRect, &sdlDstRect);
	}

	std::unique_ptr<ITexture> SDL2Context::CreateTexture(std::string_view filepath)
	{
		return std::make_unique<SDL2Texture>(m_pRenderer, filepath);
	}
}
