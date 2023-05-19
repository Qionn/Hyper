#ifndef __HYPER_SCENE_H__
#define __HYPER_SCENE_H__

#include <memory>
#include <vector>

#include "hyper/scene/actor.h"
#include "hyper/fwd.h"

namespace hyper
{
	class Scene final
	{
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
		std::vector<std::unique_ptr<Actor>> m_OwnedActors;
	};
}

#endif // !__HYPER_SCENE_H__
