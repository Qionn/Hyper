#ifndef __HYPER_PHYSICS_EVENTS_H__
#define __HYPER_PHYSICS_EVENTS_H__

#include "hyper/event/event.h"
#include "hyper/fwd.h"

namespace hyper
{
	class OverlapBeginEvent final : public AEvent
	{
	public:
		Actor& actorA;
		Actor& actorB;

	public:
		OverlapBeginEvent(Actor& a, Actor& b)
			: actorA{ a }, actorB{ b } {}

		bool IsInvolved(const Actor* pRelevant, Actor*& out) const
		{
			if (pRelevant == &actorA || pRelevant == &actorB)
			{
				out = (pRelevant == &actorA) ? &actorB : &actorA;
				return true;
			}

			return false;
		}
	};

	class OverlapEndEvent final : public AEvent
	{
	public:
		Actor& actorA;
		Actor& actorB;

	public:
		OverlapEndEvent(Actor& a, Actor& b)
			: actorA{ a }, actorB{ b } {}

		bool IsInvolved(const Actor* pRelevant, Actor*& out) const
		{
			if (pRelevant == &actorA || pRelevant == &actorB)
			{
				out = (pRelevant == &actorA) ? &actorB : &actorA;
				return true;
			}

			return false;
		}
	};
}

#endif // !__HYPER_PHYSICS_EVENTS_H__
