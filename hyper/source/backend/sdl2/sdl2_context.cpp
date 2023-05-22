#include "sdl2_context.h"
#include "sdl2_texture.h"

namespace hyper
{
	SDL2Context::SDL2Context(SDL_Renderer* pRenderer)
		: m_pRenderer{ pRenderer }
	{

	}

	void SDL2Context::DrawTexture(const ITexture& texture, const glm::vec2& pos) const
	{
		DrawTexture(texture, pos, (float)texture.GetWidth(), (float)texture.GetHeight());
	}

	void SDL2Context::DrawTexture(const ITexture& texture, const glm::vec2& pos, float width, float height) const
	{
		DrawTexture(texture, pos.x, pos.y, width, height);
	}

	void SDL2Context::DrawTexture(const ITexture& texture, float x, float y) const
	{
		DrawTexture(texture, x, y, (float)texture.GetWidth(), (float)texture.GetHeight());
	}

	void SDL2Context::DrawTexture(const ITexture& texture, float x, float y, float width, float height) const
	{
		const auto& sdl2Texture = reinterpret_cast<const SDL2Texture&>(texture);

		SDL_FRect rect = {};
		rect.x = x;
		rect.y = y;
		rect.w = width;
		rect.h = height;

		SDL_RenderCopyF(m_pRenderer, sdl2Texture.GetSDLTexture(), nullptr, &rect);
	}

	std::unique_ptr<ITexture> SDL2Context::CreateTexture(std::string_view filepath)
	{
		return std::make_unique<SDL2Texture>(m_pRenderer, filepath);
	}
}
