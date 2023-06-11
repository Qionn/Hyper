#ifndef __BURGER_TIME_PLAYER_COMPONENT_H__
#define __BURGER_TIME_PLAYER_COMPONENT_H__

#include <hyper/scene/component.h>
#include <hyper/fwd.h>

namespace burger_time
{
	class PlayerComponent final : public hyper::AComponent
	{
	public:
		PlayerComponent(hyper::Actor& actor);
		~PlayerComponent() = default;

	private:
		void OnUpdate(float dt) override;
		void OnRender(const hyper::IContext& context) const override;
	};
}

#endif // !__BURGER_TIME_PLAYER_COMPONENT_H__
