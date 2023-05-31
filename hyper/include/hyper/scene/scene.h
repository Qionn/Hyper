#ifndef __HYPER_SCENE_H__
#define __HYPER_SCENE_H__

#include <memory>
#include <queue>
#include <vector>

#include "hyper/scene/actor.h"
#include "hyper/fwd.h"

namespace hyper
{
	class Scene final
	{
	public:
		explicit Scene(IContext& context);

		void Update(float dt);
		void Render() const;
		
		Actor* CreateActor();
		Actor* CreateAndAddActor();
		void AddActor(Actor* pActor);

		void PurgeActor(const Actor* pActor);
		void PurgeAllActors();
		void DeletePurgedActors();

		void Clear();

		IContext& GetContext() const;

		Scene(const Scene&)				= delete;
		Scene(Scene&&)					= delete;
		Scene& operator=(const Scene&)	= delete;
		Scene& operator=(Scene&&)		= delete;

		~Scene() = default;

	private:
		IContext& m_Context;

		std::vector<Actor*> m_Actors;
		std::vector<Actor*> m_PurgedActors;
		std::vector<std::unique_ptr<Actor>> m_ActorPool;
	};
}

#endif // !__HYPER_SCENE_H__
