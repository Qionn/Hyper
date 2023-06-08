#ifndef __HYPER_RECT_COMPONENT_H__
#define __HYPER_RECT_COMPONENT_H__

#include <glm/vec4.hpp>

#include "hyper/scene/component.h"
#include "hyper/utils/rect.h"

namespace hyper
{
	class RectComponent final : public AComponent
	{
	public:
		RectComponent(Actor& actor, float width, float height, const glm::vec4& color);

		void SetSize(float width, float height);
		void SetColor(const glm::vec4& color);

		~RectComponent() = default;

	private:
		float m_Width, m_Height;
		glm::vec4 m_Color;

	private:
		void OnUpdate(float dt) override;
		void OnRender(const IContext& context) const override;
	};
}

#endif // !__HYPER_RECT_COMPONENT_H__
