#ifndef __HYPER_SCENE_H__
#define __HYPER_SCENE_H__

#include <memory>
#include <vector>

#include "hyper/event/subject.h"
#include "hyper/scene/actor.h"
#include "hyper/fwd.h"

namespace hyper
{
	class Scene final : public ASubject
	{
	public:
		explicit Scene(IContext& context);

		void Update(float dt);
		void Render() const;
		
		void RequestStop();
		void RequestLoad(std::function<void(Scene&, Input&)> loadScene);

		Actor* CreateActor();
		void RemoveActor(Actor* pActor);
		void RemoveAllActors();

		void EraseRemovedActors();

		IContext& GetContext() const;

		~Scene() = default;

	private:
		IContext& m_Context;

		std::vector<std::unique_ptr<Actor>> m_Actors;
		std::vector<Actor*> m_RemovedActors;
	};
}

#endif // !__HYPER_SCENE_H__
