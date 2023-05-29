#ifndef __HYPER_SCENE_FACTORY_H__
#define __HYPER_SCENE_FACTORY_H__

#include <functional>
#include <memory>
#include <vector>
#include <queue>

#include "hyper/scene/actor.h"
#include "hyper/scene/scene.h"

namespace hyper
{
	class SceneFactory final
	{
	public:
		SceneFactory() = default;

		void AddActor(const std::function<void(Scene&, Actor&)>& createActor);
		void AddActor(const std::function<void(Actor&)>& createActor);

		std::unique_ptr<Scene> CreateScene(IContext& context) const;
		void PopulateScene(Scene& scene) const;

		SceneFactory(const SceneFactory&)				= default;
		SceneFactory(SceneFactory&&)					= default;
		SceneFactory& operator=(const SceneFactory&)	= default;
		SceneFactory& operator=(SceneFactory&&)			= default;

		~SceneFactory() = default;

	private:
		std::vector<std::function<void(Scene&, Actor&)>> m_CreateActorInfo;
	};
}

#endif // !__HYPER_SCENE_FACTORY_H__
