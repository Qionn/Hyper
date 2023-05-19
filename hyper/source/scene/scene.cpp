#include "hyper/scene/actor.h"
#include "hyper/scene/scene.h"
#include "hyper/utils/assert.h"

#include <algorithm>

namespace hyper
{
	void Scene::Update()
	{
		for (Actor* pActor : m_Actors)
		{
			pActor->Update();
		}
	}

	void Scene::Render() const
	{
		for (const Actor* pActor : m_Actors)
		{
			pActor->Render();
		}
	}

	void Scene::AddActor(Actor* pActor)
	{
		HyperAssert(pActor->GetScene() == this, "pActor does not belong to this scene");
		m_Actors.push_back(pActor);
	}

	void Scene::RemoveActor(const Actor* pActor)
	{
		auto it = std::ranges::find(m_Actors, pActor);
		if (it != m_Actors.end())
		{
			m_Actors.erase(it);
		}
	}

	Actor* Scene::CreateActor()
	{
		auto pActor = new Actor(this);
		m_OwnedActors.emplace_back(std::unique_ptr<Actor>(pActor));
		return pActor;
	}
}
