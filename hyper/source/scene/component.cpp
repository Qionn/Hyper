#include "hyper/scene/actor.h"
#include "hyper/scene/component.h"

namespace hyper
{
	AComponent::AComponent(Actor& actor)
		: m_Actor{ actor }
	{

	}

	Actor& AComponent::GetActor() const
	{
		return m_Actor;
	}

	Actor* AComponent::GetActorParent() const
	{
		return m_Actor.GetParent();
	}

	Scene& AComponent::GetScene() const
	{
		return m_Actor.GetScene();
	}
}
