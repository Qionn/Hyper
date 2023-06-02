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
		for (auto& pActor : m_Actors)
		{
			if (!pActor->HasParent())
			{
				pActor->Update(dt);
			}
			else
			{
				LogWarn("Removing actor {} from scene root, because it is a child actor", (void*)pActor.get());
				RemoveActor(pActor.get());
			}
		}

		EraseRemovedActors();
	}

	void Scene::Render() const
	{
		for (const auto& pActor : m_Actors)
		{
			pActor->Render(m_Context);
		}
	}

	void Scene::AddActor(std::shared_ptr<Actor> pActor)
	{
		HyperAssert(pActor->GetScene() == this, "pActor does not belong to this scene");
		m_Actors.push_back(std::move(pActor));
	}

	void Scene::RemoveActor(Actor* pActor)
	{
		HyperAssert(pActor->GetScene() == this, "pActor does not belong to this scene");
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
