#include "hyper/scene/scene.h"
#include "hyper/utils/assert.h"

#include <algorithm>

namespace hyper
{
	Scene::Scene(IContext& context)
		: m_Context{ context }
	{

	}

	void Scene::Update(float dt)
	{
		EraseRemovedActors();

		for (auto& pActor : m_Actors)
		{
			if (pActor->IsEnabled() && !pActor->HasParent())
			{
				pActor->Update(dt);
			}
		}
	}

	void Scene::Render() const
	{
		for (const auto& pActor : m_Actors)
		{
			if (pActor->IsEnabled() && !pActor->HasParent())
			{
				pActor->Render();
			}
		}
	}

	Actor* Scene::CreateActor()
	{
		m_Actors.push_back(std::make_unique<Actor>(*this));
		return m_Actors.back().get();
	}

	void Scene::RemoveActor(Actor* pActor)
	{
		HyperAssert(&pActor->GetScene() == this, "pActor does not belong to this scene");
		m_RemovedActors.push_back(pActor);
	}

	void Scene::RemoveAllActors()
	{
		for (auto& pActor : m_Actors)
		{
			RemoveActor(pActor.get());
		}
	}

	void Scene::EraseRemovedActors()
	{
		for (auto& pActor : m_RemovedActors)
		{
			auto pred = [pActor](const auto& pA) { return pA.get() == pActor; };
			m_Actors.erase(std::remove_if(m_Actors.begin(), m_Actors.end(), pred), m_Actors.end());
		}
		m_RemovedActors.clear();
	}

	IContext& Scene::GetContext() const
	{
		return m_Context;
	}
}
