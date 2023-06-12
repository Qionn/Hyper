#ifndef __HYPER_PHYSICS_WORLD_H__
#define __HYPER_PHYSICS_WORLD_H__

#include <vector>
#include <unordered_set>

#include "hyper/event/subject.h"
#include "hyper/fwd.h"

namespace hyper
{
	class PhysicsWorld final : public ASubject
	{
	public:
		using Collider = ColliderComponent;

	public:
		PhysicsWorld() = default;

		void Update();

		void AddCollider(Collider* pCollider);
		void RemoveCollider(Collider* pCollider);
		void RemoveAllColliders();

		void EraseRemovedColliders();

		PhysicsWorld(const PhysicsWorld&)				= delete;
		PhysicsWorld(PhysicsWorld&&)					= delete;
		PhysicsWorld& operator=(const PhysicsWorld&)	= delete;
		PhysicsWorld& operator=(PhysicsWorld&&)			= delete;

		~PhysicsWorld() = default;

	private:
		std::unordered_set<Collider*> m_Colliders;
		std::vector<Collider*> m_RemovedColliders;
		std::vector<std::pair<Collider*, Collider*>> m_OverlappingColliders;

	private:
		void CheckOverlap(Collider* pA, Collider* pB);
	};
}

#endif // !__HYPER_PHYSICS_WORLD_H__
