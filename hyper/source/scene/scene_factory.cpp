#include "hyper/scene/scene_factory.h"

#include <memory>

namespace hyper
{
	void SceneFactory::AddActor(const std::function<void(SceneFactory&, Actor&)>& createActor)
	{
		m_CreateActorFunctions.emplace_back(m_pPrevActor, createActor);
	}

	void SceneFactory::AddActor(const std::function<void(Actor&)>& createActor)
	{
		m_CreateActorFunctions.emplace_back(
			m_pPrevActor,
			[createActor](SceneFactory&, Actor& actor) {
				createActor(actor);
			}
		);
	}

	std::unique_ptr<Scene> SceneFactory::CreateScene()
	{
		auto pScene = std::make_unique<Scene>();
		
		size_t actorIndex = 0;
		while (actorIndex < m_CreateActorFunctions.size())
		{
			auto [pPrevActor, createActor] = m_CreateActorFunctions[actorIndex];
			
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
