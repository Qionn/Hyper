#include "hyper/scene/actor.h"
#include "hyper/scene/component.h"
#include "hyper/utils/assert.h"

namespace hyper
{
	AComponent::AComponent(Actor* pActor)
		: m_pActor{ pActor }
	{
		HyperAssert(pActor != nullptr, "pActor must point to a valid memory address");
	}

	Actor* AComponent::GetActor() const
	{
		return m_pActor;
	}

	Actor* AComponent::GetActorParent() const
	{
		return m_pActor->GetParent();
	}
}
