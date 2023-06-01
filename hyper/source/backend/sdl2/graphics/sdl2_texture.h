#ifndef __HYPER_SDL2_TEXTURE_H__
#define __HYPER_SDL2_TEXTURE_H__

#include <SDL.h>

#include "hyper/graphics/texture.h"

namespace hyper
{
	class SDL2Texture final : public ITexture
	{
	public:
		SDL2Texture(SDL_Texture* pTexture);

		int GetWidth() const override;
		int GetHeight() const override;

		SDL_Texture* GetSDLTexture() const;

		SDL2Texture(const SDL2Texture&)				= delete;
		SDL2Texture(SDL2Texture&&)					= delete;
		SDL2Texture& operator=(const SDL2Texture&)	= delete;
		SDL2Texture& operator=(SDL2Texture&&)		= delete;

		~SDL2Texture();

	private:
		SDL_Texture* m_pTexture;
		int m_Width, m_Height;
	};
}

#endif // !__HYPER_SDL2_TEXTURE_H__
