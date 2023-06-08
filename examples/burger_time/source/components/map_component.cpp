#include "map_component.h"

#include "parsers/map_parser.h"

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
	}

	void MapComponent::OnUpdate(float)
	{

	}

	void MapComponent::OnRender(const IContext&) const
	{

	}

	void MapComponent::CreateBackgrounds(const MapParser& parser)
	{
		Actor& root = GetActor();

		for (const std::string& bg : parser.GetBackgrounds())
		{
			Actor* pActor = root.CreateChild();
			pActor->AddComponent<SpriteComponent>(bg);
		}
	}
}
