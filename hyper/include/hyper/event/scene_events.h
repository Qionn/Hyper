#ifndef __HYPER_SCENE_EVENT_H__
#define __HYPER_SCENE_EVENT_H__

#include <functional>

#include "hyper/event/event.h"
#include "hyper/fwd.h"

namespace hyper
{
	class SceneStopRequestEvent final : public AEvent
	{
	public:
		Scene& scene;

	public:
		SceneStopRequestEvent(Scene& scene)
			: scene{ scene } {}
	};

	class SceneLoadRequestEvent final : public AEvent
	{
	public:
		Scene& scene;
		std::function<void(Scene&, Input&)> loadScene;

	public:
		SceneLoadRequestEvent(Scene& scene, std::function<void(Scene&, Input&)> loadScene)
			: scene{ scene }, loadScene{ std::move(loadScene) } {}
	};
}

#endif // !__HYPER_SCENE_EVENT_H__
