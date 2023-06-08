#ifndef __HYPER_CONTEXT_H__
#define __HYPER_CONTEXT_H__

#include <memory>

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include "hyper/graphics/texture.h"
#include "hyper/utils/rect.h"

namespace hyper
{
	class IContext
	{
	public:
		virtual void DrawTexture(const ITexture& texture, const Rectf& dstRect) const = 0;
		virtual void DrawTexture(const ITexture& texture, const Recti& srcRect, const Rectf& dstRect) const = 0;

		virtual void DrawRect(const Rectf& rect, const glm::vec4& color) const = 0;

		virtual std::unique_ptr<ITexture> CreateTexture(std::string_view filepath) = 0;
		virtual std::unique_ptr<ITexture> CreateTexture(std::string_view fontFilepath, int ptSize, std::string_view text, const glm::vec3& color) = 0;

		virtual ~IContext() = default;
	};
}

#endif // !__HYPER_CONTEXT_H__
