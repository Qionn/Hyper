#include "hyper/event/physics_events.h"
#include "hyper/scene/components/collider_component.h"
#include "hyper/physics/physics_world.h"

#include <algorithm>

namespace hyper
{
	void PhysicsWorld::Update()
	{
		for (Collider* pColA : m_Colliders)
		{
			for (Collider* pColB : m_Colliders)
			{
				if (pColA != pColB)
				{
					CheckOverlap(pColA, pColB);
				}
			}
		}
	}

	void PhysicsWorld::AddCollider(Collider* pCollider)
	{
		m_Colliders.insert(pCollider);
	}

	void PhysicsWorld::RemoveCollider(Collider* pCollider)
	{
		m_Colliders.erase(pCollider);
	}

	void PhysicsWorld::CheckOverlap(Collider* pA, Collider* pB)
	{
		auto overlapIt = std::ranges::find_if(m_OverlappingColliders, [=](const auto& overlap) {
			return ((overlap.first == pA && overlap.second == pB) ||
					(overlap.first == pB && overlap.second == pA));
		});

		if (pA->IsOverlapping(*pB))
		{
			if (overlapIt == m_OverlappingColliders.end())
			{
				m_OverlappingColliders.push_back({ pA, pB });
				OverlapBeginEvent e(pA->GetActor(), pB->GetActor());
				NotifyObservers(e);
			}
		}
		else
		{
			if (overlapIt != m_OverlappingColliders.end())
			{
				m_OverlappingColliders.erase(overlapIt);
				OverlapEndEvent e(pA->GetActor(), pB->GetActor());
				NotifyObservers(e);
			}
		}
	}
}
