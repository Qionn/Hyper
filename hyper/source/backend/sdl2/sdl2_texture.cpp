#include "sdl2_texture.h"

#include "hyper/utils/logging.h"

#include <SDL_image.h>

namespace hyper
{
	SDL2Texture::SDL2Texture(SDL_Renderer* pRenderer, std::string_view filepath)
	{
		m_pTexture = IMG_LoadTexture(pRenderer, filepath.data());

		if (m_pTexture == nullptr)
		{
			LogWarn("Failed to load SDL2 texture '{}'", filepath);
		}

		SDL_QueryTexture(m_pTexture, nullptr, nullptr, &m_Width, &m_Height);
	}

	SDL2Texture::~SDL2Texture()
	{
		SDL_DestroyTexture(m_pTexture);
	}

	int SDL2Texture::GetWidth() const
	{
		return m_Width;
	}

	int SDL2Texture::GetHeight() const
	{
		return m_Height;
	}

	SDL_Texture* SDL2Texture::GetSDLTexture() const
	{
		return m_pTexture;
	}
}
