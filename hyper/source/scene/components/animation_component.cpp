#include "hyper/scene/components/animation_component.h"
#include "hyper/scene/components/sprite_component.h"
#include "hyper/scene/actor.h"
#include "hyper/utils/assert.h"

namespace hyper
{

	AnimationComponent::AnimationComponent(Actor& actor, float frameTime, int numFrames)
		: AComponent(actor)
		, m_FrameTime{ frameTime }
		, m_NumFrames{ numFrames }
	{
		m_pSprite = actor.GetComponent<SpriteComponent>();
		HyperAssert(m_pSprite != nullptr, "Expected the actor to have a SpriteComponent when animating");

		m_ClipRect.x = 0;
		m_ClipRect.y = 0;
		m_ClipRect.width = static_cast<int>(m_pSprite->GetWidth() / numFrames);
		m_ClipRect.height = static_cast<int>(m_pSprite->GetHeight());
		m_pSprite->SetClipRect(m_ClipRect);
	}

	void AnimationComponent::OnUpdate(float dt)
	{
		m_Timer += dt;

		if (m_Timer >= m_FrameTime)
		{
			m_CurrentFrame = (m_CurrentFrame + 1) % m_NumFrames;
			m_ClipRect.x = m_ClipRect.width * m_CurrentFrame;
			m_Timer -= m_FrameTime;
			m_pSprite->SetClipRect(m_ClipRect);
		}
	}

	void AnimationComponent::OnRender(const IContext&) const
	{

	}
}
