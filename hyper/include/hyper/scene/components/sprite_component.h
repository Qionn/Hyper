#ifndef __HYPER_SPRITE_H__
#define __HYPER_SPRITE_H__

#include <memory>

#include "hyper/graphics/texture.h"
#include "hyper/scene/component.h"

namespace hyper
{
	class SpriteComponent final : public AComponent
	{
	public:
		SpriteComponent(Actor* pActor, std::string_view filepath);
		~SpriteComponent() = default;

		void SetSize(float width, float height);

	private:
		float m_Width, m_Height;
		std::unique_ptr<ITexture> m_pTexture;

	private:
		void OnUpdate() override;
		void OnRender() const override;
	};
}

#endif // !__HYPER_SPRITE_H__
