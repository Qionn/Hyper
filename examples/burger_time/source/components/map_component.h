#ifndef __BURGER_TIME_MAP_COMPONENT_H__
#define __BURGER_TIME_MAP_COMPONENT_H__

#include <string_view>

#include <hyper/scene/component.h>

namespace burger_time
{
	class MapParser;

	class MapComponent final : public hyper::AComponent
	{
	public:
		MapComponent(hyper::Actor& actor, std::string_view mapFile);
		~MapComponent() = default;

	private:
		void OnUpdate(float dt) override;
		void OnRender(const hyper::IContext& context) const override;

		void CreateBackgrounds(const MapParser& parser);
	};
}

#endif // !__BURGER_TIME_MAP_COMPONENT_H__
