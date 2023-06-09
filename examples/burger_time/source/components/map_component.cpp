#include "map_component.h"

#include <hyper/scene/components/sprite_component.h>
#include <hyper/scene/actor.h>

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
	}

	const std::vector<MapComponent::Platform>& MapComponent::GetPlatforms() const
	{
		return m_Platforms;
	}

	const std::vector<MapComponent::Ladder>& MapComponent::GetLadders() const
	{
		return m_Ladder;
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

			m_Ladder.push_back(ladder);
		}
	}

	void MapComponent::OnUpdate(float)
	{

	}

	void MapComponent::OnRender(const IContext&) const
	{

	}
}
