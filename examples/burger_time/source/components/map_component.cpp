#include "map_component.h"

#include "components/ingredient_component.h"

#include <hyper/scene/components/collider_component.h>
#include <hyper/scene/components/sprite_component.h>
#include <hyper/scene/scene.h>

using namespace hyper;

namespace burger_time
{
	MapComponent::MapComponent(Actor& actor, std::string_view mapFile)
		: AComponent(actor)
	{
		MapParser parser(mapFile);
		CreateBackgrounds(parser);
		CreatePlatforms(parser);
		CreateLadders(parser);
		CreateIngredients(parser);
	}

	const std::vector<MapComponent::Platform>& MapComponent::GetPlatforms() const
	{
		return m_Platforms;
	}

	const std::vector<MapComponent::Ladder>& MapComponent::GetLadders() const
	{
		return m_Ladders;
	}

	const MapComponent::Platform* MapComponent::GetNearestPlatform(const glm::vec2& pos, float range) const
	{
		const Platform* pPlatform = nullptr;
		float distance = FLT_MAX;

		for (const auto& platform : m_Platforms)
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

	const MapComponent::Ladder* MapComponent::GetNearestLadder(const glm::vec2& pos, float range) const
	{
		const Ladder* pLadder = nullptr;
		float distance = FLT_MAX;

		for (const auto& ladder : m_Ladders)
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

	void MapComponent::CreateBackgrounds(const MapParser& parser)
	{
		Actor* pActor = GetActor().CreateChild();
		auto pSprite = pActor->AddComponent<SpriteComponent>(parser.GetBackground());

		glm::vec2 pos = pActor->GetWorldPosition();
		m_TopLeft.x = pos.x - pSprite->GetWidth() * 0.5f;
		m_TopLeft.y = pos.y - pSprite->GetHeight() * 0.5f;
	}

	void MapComponent::CreatePlatforms(const MapParser& parser)
	{
		for (const auto& plat : parser.GetPlatforms())
		{
			Platform platform;
			platform.minX = plat.minX + m_TopLeft.x;
			platform.maxX = plat.maxX + m_TopLeft.x;
			platform.height = plat.height + m_TopLeft.y;

			m_Platforms.push_back(platform);
		}
	}

	void MapComponent::CreateLadders(const MapParser& parser)
	{
		for (const auto& lad : parser.GetLadders())
		{
			Ladder ladder;
			ladder.bottom = lad.bottom + m_TopLeft.y;
			ladder.top = lad.top + m_TopLeft.y;
			ladder.posX = lad.posX + m_TopLeft.x;

			m_Ladders.push_back(ladder);
		}
	}

	void MapComponent::CreateIngredients(const MapParser& parser)
	{
		Scene& scene = GetScene();

		for (const auto& ing : parser.GetIngredients())
		{
			auto type = static_cast<IngredientType>(ing.type);

			glm::vec2 pos;
			pos.x = m_TopLeft.x + ing.posX;
			pos.y = m_TopLeft.y + ing.posY;

			Actor* pActor = scene.CreateActor();
			pActor->SetPosition(pos);
			pActor->AddComponent<ColliderComponent>(93.0f, 21.0f);
			pActor->AddComponent<IngredientComponent>(type, this);
		}
	}

	void MapComponent::OnUpdate(float)
	{

	}

	void MapComponent::OnRender(const IContext&) const
	{

	}
}
