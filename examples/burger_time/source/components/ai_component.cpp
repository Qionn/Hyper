#include "ai_component.h"

#include <hyper/scene/actor.h>
#include <hyper/utils/assert.h>

#include <glm/glm.hpp>

using namespace hyper;

namespace burger_time
{

	AIComponent::AIComponent(Actor& actor, Actor* pTargetActor)
		: AComponent(actor)
		, m_pTargetActor{ pTargetActor }
	{
		m_pCharacter = GetActor().GetComponent<CharacterComponent>();
		HyperAssert(m_pCharacter != nullptr, "The AIComponent requires a CharacterComponent to function propperly");
	}

	void AIComponent::SetTargetActor(Actor* pActor)
	{
		m_pTargetActor = pActor;
	}

	Actor* AIComponent::GetTargetActor() const
	{
		return m_pTargetActor;
	}

	void AIComponent::OnUpdate(float)
	{
		if (m_pCharacter != nullptr && m_pTargetActor != nullptr)
		{
			glm::vec2 direction = m_pTargetActor->GetWorldPosition() - GetActor().GetWorldPosition();

			if (m_pCharacter->IsOnLadder())
			{
				if (std::abs(direction.y) > 0.1f)
				{
					direction.y = 1 * glm::sign(direction.y);
					direction.x = 0;
				}
				else
				{
					direction.y = 0;
					direction.x = 1 * glm::sign(direction.x);
				}
			}

			if (m_pCharacter->IsOnPlatform())
			{
				if (std::abs(direction.x) > 1.0f)
				{
					direction.x = 1 * glm::sign(direction.x);
					direction.y = 0;
				}
				else
				{
					direction.y = 1 * glm::sign(direction.y);
					direction.x = 0;
				}
			}

			m_pCharacter->Move(direction);
		}
	}

	void AIComponent::OnRender(const IContext&) const
	{

	}
}
