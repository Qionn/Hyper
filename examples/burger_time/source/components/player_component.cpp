#include "player_component.h"

#include <hyper/event/dispatcher.h>
#include <hyper/scene/scene.h>

#include "components/enemy_component.h"
#include "events/scene_events.h"

using namespace hyper;

namespace burger_time
{
	PlayerComponent::PlayerComponent(hyper::Actor& actor)
		: AComponent(actor)
	{
		GetScene().GetPhysicsWorld().AddObserver(this);
	}

	PlayerComponent::~PlayerComponent()
	{
		GetScene().GetPhysicsWorld().RemoveObserver(this);
	}

	void PlayerComponent::OnUpdate(float)
	{

	}

	void PlayerComponent::OnRender(const hyper::IContext&) const
	{

	}

	bool PlayerComponent::OnEvent(const hyper::AEvent& event)
	{
		Dispatcher dispatcher(event);

		dispatcher.Dispatch(&PlayerComponent::OnOverlapBeginEvent, this);

		return dispatcher.IsEventHandled();
	}

	bool PlayerComponent::OnOverlapBeginEvent(const hyper::OverlapBeginEvent& event)
	{
		Actor* pOwner = &GetActor();
		Actor* pOther = nullptr;

		if (event.IsInvolved(pOwner, pOther))
		{
			auto pEnemy = pOther->GetComponent<EnemyComponent>();
			if (pEnemy != nullptr)
			{
				PlayerHitEvent e(pOwner);
				NotifyObservers(e);
			}
		}

		return false;
	}
}
