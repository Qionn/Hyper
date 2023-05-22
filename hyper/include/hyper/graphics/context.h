#ifndef __HYPER_CONTEXT_H__
#define __HYPER_CONTEXT_H__

#include <memory>

#include <glm/vec2.hpp>

#include "hyper/graphics/texture.h"

namespace hyper
{
	class IContext
	{
	public:
		virtual void DrawTexture(const ITexture& texture, const glm::vec2& pos) const = 0;
		virtual void DrawTexture(const ITexture& texture, const glm::vec2& pos, float width, float height) const = 0;
		virtual void DrawTexture(const ITexture& texture, float x, float y) const = 0;
		virtual void DrawTexture(const ITexture& texture, float x, float y, float width, float height) const = 0;

		virtual std::unique_ptr<ITexture> CreateTexture(std::string_view filepath) = 0;

		virtual ~IContext() = default;
	};
}

#endif // !__HYPER_CONTEXT_H__
