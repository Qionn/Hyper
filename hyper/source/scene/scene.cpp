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
		DeletePurgedActors();

		for (Actor* pActor : m_Actors)
		{
			pActor->Update(dt);
		}
	}

	void Scene::Render() const
	{
		for (const Actor* pActor : m_Actors)
		{
			pActor->Render(m_Context);
		}
	}

	Actor* Scene::CreateActor()
	{
		auto pActor = new Actor(*this);
		m_ActorPool.emplace_back(std::unique_ptr<Actor>(pActor));
		return pActor;
	}

	Actor* Scene::CreateAndAddActor()
	{
		Actor* pActor = CreateActor();
		AddActor(pActor);
		return pActor;
	}

	void Scene::AddActor(Actor* pActor)
	{
		HyperAssert(pActor->GetScene() == this, "pActor does not belong to this scene");
		m_Actors.push_back(pActor);
	}

	void Scene::PurgeActor(const Actor* pActor)
	{
		if (auto it = std::ranges::find(m_Actors, pActor); it != m_Actors.end())
		{
			m_PurgedActors.push_back(*it);
		}
	}

	void Scene::PurgeAllActors()
	{
		for (Actor* pActor : m_Actors)
		{
			PurgeActor(pActor);
		}
	}

	void Scene::DeletePurgedActors()
	{
		while (!m_PurgedActors.empty())
		{
			Actor* pActor = m_PurgedActors.back();
			m_PurgedActors.pop_back();

			pActor->ForEachChild([](Actor& child) {
				child.SetParent(nullptr, false);
			});

			if (auto it = std::ranges::find(m_Actors, pActor); it != m_Actors.end())
			{
				m_Actors.erase(it);
			}

			auto pred = [pActor](const auto& pA) { return pA.get() == pActor; };
			if (auto it = std::ranges::find_if(m_ActorPool, pred); it != m_ActorPool.end())
			{
				m_ActorPool.erase(it);
			}
		}
	}

	void Scene::Clear()
	{
		m_Actors.clear();
		m_PurgedActors.clear();
		m_ActorPool.clear();
	}

	IContext& Scene::GetContext() const
	{
		return m_Context;
	}
}
