#include "sdl2_context.h"
#include "sdl2_texture.h"

#include "hyper/utils/logging.h"

#include <SDL_image.h>
#include <SDL_ttf.h>

#include <algorithm>

namespace hyper
{
	SDL2Context::SDL2Context(SDL_Renderer* pRenderer)
		: m_pRenderer{ pRenderer }
	{
		IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
		TTF_Init();
	}

	SDL2Context::~SDL2Context()
	{
		TTF_Quit();
		IMG_Quit();
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

	void SDL2Context::DrawRect(const Rectf& rect, const glm::vec4& color) const
	{
		SDL_FRect sdlRect = {
			.x = rect.x,
			.y = rect.y,
			.w = rect.width,
			.h = rect.height
		};

		SDL_Color sdlColor = {
			static_cast<Uint8>(std::clamp(color.r * 255, 0.0f, 255.0f)),
			static_cast<Uint8>(std::clamp(color.g * 255, 0.0f, 255.0f)),
			static_cast<Uint8>(std::clamp(color.b * 255, 0.0f, 255.0f)),
			static_cast<Uint8>(std::clamp(color.a * 255, 0.0f, 255.0f))
		};

		SDL_Color prevColor{};

		SDL_GetRenderDrawColor(m_pRenderer, &prevColor.r, &prevColor.g, &prevColor.b, &prevColor.a);
		SDL_SetRenderDrawColor(m_pRenderer, sdlColor.r, sdlColor.g, sdlColor.b, sdlColor.a);
		SDL_RenderFillRectF(m_pRenderer, &sdlRect);
		SDL_SetRenderDrawColor(m_pRenderer, prevColor.r, prevColor.g, prevColor.b, prevColor.a);
	}

	std::unique_ptr<ITexture> SDL2Context::CreateTexture(std::string_view filepath)
	{
		SDL_Texture* pTexture = IMG_LoadTexture(m_pRenderer, filepath.data());
		if (pTexture == nullptr)
		{
			LogWarn("Missing texture '{}': {}", filepath, IMG_GetError());
		}

		return std::make_unique<SDL2Texture>(pTexture);
	}

	std::unique_ptr<ITexture> SDL2Context::CreateTexture(std::string_view fontFilepath, int ptSize, std::string_view text, const glm::vec3& color)
	{
		TTF_Font* pFont = TTF_OpenFont(fontFilepath.data(), ptSize);
		if (pFont == nullptr)
		{
			LogWarn("Missing font: '{}': {}", fontFilepath, TTF_GetError());
		}

		SDL_Color sdlColor = {
			static_cast<Uint8>(std::clamp(color.r * 255, 0.0f, 255.0f)),
			static_cast<Uint8>(std::clamp(color.g * 255, 0.0f, 255.0f)),
			static_cast<Uint8>(std::clamp(color.b * 255, 0.0f, 255.0f)),
			255
		};

		SDL_Surface* pSurface = TTF_RenderText_Solid(pFont, text.data(), sdlColor);
		if (pSurface == nullptr)
		{
			LogTrace("Missing font (surface): {}", TTF_GetError());
		}

		SDL_Texture* pTexture = SDL_CreateTextureFromSurface(m_pRenderer, pSurface);
		if (pTexture == nullptr)
		{
			LogTrace("Missing font (texture): {}", SDL_GetError());
		}

		SDL_FreeSurface(pSurface);
		TTF_CloseFont(pFont);

		return std::make_unique<SDL2Texture>(pTexture);
	}
}
