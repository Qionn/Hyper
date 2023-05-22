#include "hyper/scene/scene_factory.h"

#include <memory>

namespace hyper
{
	void SceneFactory::AddActor(const std::function<void(SceneFactory&, Actor&)>& createActor)
	{
		m_CreateActorInfo.emplace_back(m_pPrevActor, createActor);
	}

	void SceneFactory::AddActor(const std::function<void(Actor&)>& createActor)
	{
		m_CreateActorInfo.emplace_back(
			m_pPrevActor,
			[createActor](SceneFactory&, Actor& actor) {
				createActor(actor);
			}
		);
	}

	std::unique_ptr<Scene> SceneFactory::CreateScene(hyper::IContext& context)
	{
		auto pScene = std::make_unique<Scene>(context);
		
		size_t actorIndex = 0;
		while (actorIndex < m_CreateActorInfo.size())
		{
			auto [pPrevActor, createActor] = m_CreateActorInfo[actorIndex];
			
			Actor* pActor = pScene->CreateActor();
			pActor->SetParent(pPrevActor, false);
		
			m_pPrevActor = pActor;
			createActor(*this, *pActor);
			m_pPrevActor = nullptr;

			if (pPrevActor == nullptr)
			{
				pScene->AddActor(pActor);
			}
		
			++actorIndex;
		}

		return pScene;
	}
}
