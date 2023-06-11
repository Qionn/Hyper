#ifndef __BURGER_TIME_MAP_COMPONENT_H__
#define __BURGER_TIME_MAP_COMPONENT_H__

#include <string_view>
#include <vector>

#include <glm/vec2.hpp>

#include <hyper/scene/component.h>

#include "parsers/map_parser.h"

namespace burger_time
{
	class MapParser;

	class MapComponent final : public hyper::AComponent
	{
	public:
		using Platform = MapParser::Platform;
		using Ladder = MapParser::Ladder;
		using Ingredient = MapParser::Ingredient;

	public:
		MapComponent(hyper::Actor& actor, std::string_view mapFile);

		const std::vector<Platform>& GetPlatforms() const;
		const std::vector<Ladder>& GetLadders() const;

		const Platform* GetNearestPlatform(const glm::vec2& pos, float range) const;
		const Ladder* GetNearestLadder(const glm::vec2& pos, float range) const;

		~MapComponent() = default;

	private:
		glm::vec2 m_TopLeft;
		std::vector<Platform> m_Platforms;
		std::vector<Ladder> m_Ladders;

	private:
		void CreateBackgrounds(const MapParser& parser);
		void CreatePlatforms(const MapParser& parser);
		void CreateLadders(const MapParser& parser);
		void CreateIngredients(const MapParser& parser);

		void OnUpdate(float dt) override;
		void OnRender(const hyper::IContext& context) const override;
	};
}

#endif // !__BURGER_TIME_MAP_COMPONENT_H__
