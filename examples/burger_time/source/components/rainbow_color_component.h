#ifndef __BURGER_TIME_RAINBOW_COLOR_COMPONENT_H__
#define __BURGER_TIME_RAINBOW_COLOR_COMPONENT_H__

#include <hyper/scene/component.h>

#include <glm/vec3.hpp>

namespace burger_time
{
	class RainbowColorComponent final : public hyper::AComponent
	{
	public:
		RainbowColorComponent(hyper::Actor& actor, float speed);
		~RainbowColorComponent() = default;

	private:
		float m_Speed;
		float m_Degrees = 0.0f;

	private:
		void OnUpdate(float dt) override;
		void OnRender(const hyper::IContext& context) const override;

		static glm::vec3 ToRGB(float h, float s, float v);
	};
}

#endif // !__BURGER_TIME_RAINBOW_COLOR_COMPONENT_H__
