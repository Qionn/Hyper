#include "enemy_component.h"

#include <hyper/scene/actor.h>
#include <hyper/utils/assert.h>

#include <glm/glm.hpp>

using namespace hyper;

namespace burger_time
{

	EnemyComponent::EnemyComponent(Actor& actor, Type type, bool enableAI)
		: AComponent(actor)
		, m_Type{ type }
		, m_HasAI{ enableAI }
	{
		m_pCharacter = GetActor().GetComponent<CharacterComponent>();
	}

	void EnemyComponent::SetTargetActor(Actor* pActor)
	{
		m_pTargetActor = pActor;
	}

	Actor* EnemyComponent::GetTargetActor() const
	{
		return m_pTargetActor;
	}

	void EnemyComponent::OnUpdate(float)
	{
		if (m_HasAI)
		{
			if (m_pCharacter == nullptr)
			{
				m_pCharacter = GetActor().GetComponent<CharacterComponent>();
			}

			UpdateAIBrain();
		}
	}

	void EnemyComponent::OnRender(const IContext&) const
	{

	}

	void EnemyComponent::UpdateAIBrain()
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

	std::string_view EnemyComponent::GetSpritePath() const
	{
		switch (m_Type)
		{
			case Type::eHotdog: return "assets/sprites/hotdog_test.png";
			case Type::ePicke: return "assets/sprites/pickle_test.png";
			case Type::eEgg: return "assets/sprites/egg_test.png";
		}

		HyperAssert(false, "Unknown enemy type");
		return nullptr;
	}
}
