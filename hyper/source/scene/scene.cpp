#include "hyper/event/scene_events.h"
#include "hyper/scene/scene.h"
#include "hyper/utils/assert.h"

#include <algorithm>

namespace hyper
{
	Scene::Scene(IContext& context)
		: m_Context{ context }
	{
		m_pPhysicsWorld = std::make_unique<PhysicsWorld>();
	}

	void Scene::Update(float dt)
	{
		EraseRemovedActors();

		for (auto& pActor : m_Actors)
		{
			if (pActor->IsEnabled() && !pActor->HasParent())
			{
				pActor->Update(dt * m_TimeScale);
			}
		}

		m_pPhysicsWorld->Update();
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

	void Scene::RequestStop()
	{
		SceneStopRequestEvent e(*this);
		NotifyObservers(e);
	}

	void Scene::RequestLoad(std::function<void(Scene&, Input&)> loadScene)
	{
		SceneLoadRequestEvent e(*this, std::move(loadScene));
		NotifyObservers(e);
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

	void Scene::SetTimeScale(float scale)
	{
		m_TimeScale = scale;
	}

	float Scene::GetTimeScale() const
	{
		return m_TimeScale;
	}

	IContext& Scene::GetContext() const
	{
		return m_Context;
	}

	PhysicsWorld& Scene::GetPhysicsWorld() const
	{
		return *m_pPhysicsWorld;
	}
}
