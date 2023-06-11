#ifndef __HYPER_COLLIDER_COMPONENT_H__
#define __HYPER_COLLIDER_COMPONENT_H__

#include <memory>

#include "hyper/scene/component.h"

namespace hyper
{
	class ColliderComponent final : public AComponent
	{
	public:
		ColliderComponent(Actor& actor, float width, float height);

		void SetSize(float width, float height);
		bool IsOverlapping(const ColliderComponent& other) const;

		~ColliderComponent();

	private:
		float m_Width, m_Height;
		float m_HalfWidth, m_HalfHeight;

	private:
		void OnUpdate(float dt) override;
		void OnRender(const IContext& context) const override;

		static bool ValueInRange(float value, float min, float max);
	};
}

#endif // !__HYPER_COLLIDER_COMPONENT_H__
