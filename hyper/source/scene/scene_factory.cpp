#include "hyper/scene/scene_factory.h"

#include <memory>

namespace hyper
{
	void SceneFactory::AddActor(const std::function<void(Scene&, Actor&)>& createActor)
	{
		m_CreateActorInfo.push_back(createActor);
	}

	void SceneFactory::AddActor(const std::function<void(Actor&)>& createActor)
	{
		m_CreateActorInfo.push_back(
			[createActor](Scene&, Actor& actor) {
				createActor(actor);
			}
		);
	}

	std::unique_ptr<Scene> SceneFactory::CreateScene(IContext& context) const
	{
		auto pScene = std::make_unique<Scene>(context);
		PopulateScene(*pScene);
		return pScene;
	}

	void SceneFactory::PopulateScene(Scene& scene) const
	{
		scene.Clear();

		size_t actorIndex = 0;
		while (actorIndex < m_CreateActorInfo.size())
		{
			auto& createActor = m_CreateActorInfo[actorIndex];
			Actor* pActor = scene.CreateActor();

			createActor(scene, *pActor);

			scene.AddActor(pActor);

			++actorIndex;
		}
	}
}
