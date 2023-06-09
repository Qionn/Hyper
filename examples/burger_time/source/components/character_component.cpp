#include "character_component.h"

#include <hyper/scene/components/sprite_component.h>
#include <hyper/scene/actor.h>
#include <hyper/utils/assert.h>

#include <algorithm>

using namespace hyper;

namespace burger_time
{

	CharacterComponent::CharacterComponent(Actor& actor, const MapComponent* pMap, float speed)
		: AComponent(actor)
		, m_pMap{ pMap }
		, m_Speed{ speed }
	{
		auto pSprite = GetActor().GetComponent<SpriteComponent>();
		if (pSprite != nullptr)
		{
			m_Height = pSprite->GetHeight();
		}

		m_pPlatform = GetNearestPlatform(FLT_MAX);
		HyperAssert(m_pPlatform != nullptr, "No near platform was found");
		ClampPositionToPlatform(*m_pPlatform);
	}

	void CharacterComponent::Move(const glm::vec2& direction)
	{
		if (IsOnPlatform())
		{
			Actor& actor = GetActor();
			glm::vec2 pos = actor.GetLocalPosition();
			pos.x += direction.x * m_Speed * m_Deltatime;
			actor.SetPosition(pos);
			ClampPositionToPlatform(*m_pPlatform);

			if (direction.y != 0)
			{
				m_pLadder = GetNearestLadder(10.0f);
				if (m_pLadder != nullptr)
				{
					m_pPlatform = nullptr;
				}
			}
		}

		if (IsOnLadder())
		{
			Actor& actor = GetActor();
			glm::vec2 pos = actor.GetLocalPosition();
			pos.y += direction.y * m_Speed * m_Deltatime;
			actor.SetPosition(pos);
			ClampPositionToLadder(*m_pLadder);

			if (direction.x != 0)
			{
				m_pPlatform = GetNearestPlatform(10.0f);
				if (m_pPlatform != nullptr)
				{
					m_pLadder = nullptr;
				}
			}
		}
	}

	bool CharacterComponent::IsOnPlatform() const
	{
		return m_pPlatform != nullptr;
	}

	bool CharacterComponent::IsOnLadder() const
	{
		return m_pLadder != nullptr;
	}

	const CharacterComponent::Platform* CharacterComponent::GetNearestPlatform(float range) const
	{
		glm::vec2 pos = GetActor().GetWorldPosition() + glm::vec2(0, m_Height * 0.5f);

		const Platform* pPlatform = nullptr;
		float distance = FLT_MAX;

		for (const auto& platform : m_pMap->GetPlatforms())
		{
			float dist = platform.height - pos.y;

			if (platform.minX <= pos.x && platform.maxX >= pos.x &&
				dist >= 0 && dist < distance && dist <= range)
			{
				pPlatform = &platform;
				distance = dist;
			}
		}

		return pPlatform;
	}

	const CharacterComponent::Ladder* CharacterComponent::GetNearestLadder(float range) const
	{
		glm::vec2 pos = GetActor().GetWorldPosition() + glm::vec2(0, m_Height * 0.5f);

		const Ladder* pLadder = nullptr;
		float distance = FLT_MAX;

		for (const auto& ladder : m_pMap->GetLadders())
		{
			float dist = std::abs(ladder.posX - pos.x);

			if (ladder.top <= pos.y && ladder.bottom >= pos.y &&
				dist >= 0 && dist < distance && dist <= range)
			{
				pLadder = &ladder;
				distance = dist;
			}
		}

		return pLadder;
	}

	void CharacterComponent::ClampPositionToPlatform(const Platform& platform)
	{
		Actor& actor = GetActor();

		glm::vec2 pos = actor.GetWorldPosition();

		pos.x = std::clamp(pos.x, platform.minX, platform.maxX);
		pos.y = platform.height - m_Height * 0.5f;

		actor.SetPosition(pos);
	}

	void CharacterComponent::ClampPositionToLadder(const Ladder& ladder)
	{
		Actor& actor = GetActor();

		glm::vec2 pos = actor.GetWorldPosition();

		float halfHeight = m_Height * 0.5f;

		pos.x = ladder.posX;
		pos.y = std::clamp(pos.y, ladder.top - halfHeight, ladder.bottom - halfHeight);

		actor.SetPosition(pos);
	}

	void CharacterComponent::OnUpdate(float dt)
	{
		m_Deltatime = dt;
	}

	void CharacterComponent::OnRender(const IContext&) const
	{

	}
}
