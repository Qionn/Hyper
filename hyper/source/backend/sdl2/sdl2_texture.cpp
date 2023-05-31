#include "sdl2_texture.h"

#include "hyper/utils/assert.h"

namespace hyper
{
	SDL2Texture::SDL2Texture(SDL_Texture* pTexture)
		: m_pTexture{ pTexture }
	{
		HyperAssert(pTexture != nullptr, "Expected pTexture to point to valid memory");
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
