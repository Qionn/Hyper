#ifndef __HYPER_ANIMATION_COMPONENT_H__
#define __HYPER_ANIMATION_COMPONENT_H__

#include "hyper/scene/component.h"
#include "hyper/utils/rect.h"
#include "hyper/fwd.h"

namespace hyper
{
	inline float operator ""_fps(unsigned long long a)
	{
		return 1.0f / a;
	}

	class AnimationComponent final : public AComponent
	{
	public:
		AnimationComponent(Actor& actor, float frameTime, int numFrames);
		~AnimationComponent() = default;

	private:
		float m_FrameTime;
		int m_NumFrames;
		float m_Timer = 0.0f;
		int m_CurrentFrame = 0;
		Recti m_ClipRect;

		SpriteComponent* m_pSprite;

	private:
		void OnUpdate(float dt) override;
		void OnRender(const IContext& context) const override;
	};
}

#endif // !__HYPER_ANIMATION_COMPONENT_H__
