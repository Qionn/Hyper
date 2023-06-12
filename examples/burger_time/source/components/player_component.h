#ifndef __BURGER_TIME_PLAYER_COMPONENT_H__
#define __BURGER_TIME_PLAYER_COMPONENT_H__

#include <hyper/event/observer.h>
#include <hyper/event/subject.h>
#include <hyper/event/physics_events.h>
#include <hyper/scene/component.h>
#include <hyper/fwd.h>

namespace burger_time
{
	class PlayerComponent final : public hyper::AComponent, public hyper::IObserver, public hyper::ASubject
	{
	public:
		PlayerComponent(hyper::Actor& actor);
		~PlayerComponent();

	private:
		void OnUpdate(float dt) override;
		void OnRender(const hyper::IContext& context) const override;

		bool OnEvent(const hyper::AEvent& event) override;
		bool OnOverlapBeginEvent(const hyper::OverlapBeginEvent& event);
	};
}

#endif // !__BURGER_TIME_PLAYER_COMPONENT_H__
