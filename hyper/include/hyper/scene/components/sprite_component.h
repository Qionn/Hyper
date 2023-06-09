#ifndef __HYPER_SPRITE_H__
#define __HYPER_SPRITE_H__

#include <memory>
#include <string_view>

#include "hyper/graphics/texture.h"
#include "hyper/scene/component.h"
#include "hyper/utils/rect.h"

namespace hyper
{
	class SpriteComponent final : public AComponent
	{
	public:
		SpriteComponent(Actor& actor, std::string_view filepath);
		~SpriteComponent() = default;

		void SetScale(float scale);
		void SetClipRect(const Recti& rect);

		float GetWidth() const;
		float GetHeight() const;

	private:
		float m_Scale = 1.0f;
		Recti m_ClipRect;
		std::unique_ptr<ITexture> m_pTexture;

	private:
		void OnUpdate(float dt) override;
		void OnRender(const IContext& context) const override;
	};
}

#endif // !__HYPER_SPRITE_H__
