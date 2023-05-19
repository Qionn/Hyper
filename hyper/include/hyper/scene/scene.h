#ifndef __HYPER_SCENE_H__
#define __HYPER_SCENE_H__

#include <vector>

#include "hyper/memory/pool_allocator.h"
#include "hyper/fwd.h"

namespace hyper
{
	class Scene final
	{
	public:
		using ActorAllocator = PoolAllocator<Actor, 32>;

	public:
		Scene() = default;

		void Update();
		void Render() const;

		void AddActor(Actor* pActor);
		void RemoveActor(const Actor* pActor);

		Actor* CreateActor();

		Scene(const Scene&)				= delete;
		Scene(Scene&&)					= delete;
		Scene& operator=(const Scene&)	= delete;
		Scene& operator=(Scene&&)		= delete;

		~Scene() = default;

	private:
		std::vector<Actor*> m_Actors;
		ActorAllocator m_ActorAllocator;
	};
}

#endif // !__HYPER_SCENE_H__
