#include "hyper/scene/components/transform_component.h"
#include "hyper/scene/actor.h"
#include "hyper/scene/scene.h"
#include "hyper/utils/assert.h"

#include <algorithm>

namespace hyper
{
	Actor::Actor(Scene& scene)
		: m_Scene{ scene }
		, m_Context{ scene.GetContext() }
	{
		m_pTransform = AddComponent<TransformComponent>();
	}

	Actor::~Actor()
	{
		while (!m_Children.empty())
		{
			m_Children.front()->SetParent(m_pParent, false);
		}

		SetParent(nullptr, false);
	}

	void Actor::Update(float dt)
	{
		for (auto& [id, pComponent] : m_Components)
		{
			pComponent->OnUpdate(dt);
		}

		for (Actor* pChild : m_Children)
		{
			if (pChild->IsEnabled())
			{
				pChild->Update(dt);
			}
		}
	}

	void Actor::Render() const
	{
		for (const auto& [id, pComponent] : m_Components)
		{
			pComponent->OnRender(m_Context);
		}

		for (const Actor* pChild : m_Children)
		{
			if (pChild->IsEnabled())
			{
				pChild->Render();
			}
		}
	}

	void Actor::Translate(float x, float y)
	{
		glm::vec2 pos = m_pTransform->GetLocalPosition();
		pos.x += x;
		pos.y += y;
		m_pTransform->SetPosition(pos);
	}

	void Actor::Translate(const glm::vec2& translation)
	{
		glm::vec2 pos = m_pTransform->GetLocalPosition();
		pos += translation;
		m_pTransform->SetPosition(pos);
	}

	void Actor::SetPosition(float x, float y)
	{
		m_pTransform->SetPosition(x, y);
	}

	void Actor::SetPosition(const glm::vec2& position)
	{
		m_pTransform->SetPosition(position);
	}

	const glm::vec2& Actor::GetLocalPosition() const
	{
		return m_pTransform->GetLocalPosition();
	}

	const glm::vec2& Actor::GetWorldPosition() const
	{
		return m_pTransform->GetWorldPosition();
	}

	Actor* Actor::CreateChild()
	{
		Actor* pActor = m_Scene.CreateActor();
		pActor->SetParent(this, false);
		return pActor;
	}

	void Actor::SetParent(Actor* pParent, bool keepWorldPosition)
	{
		glm::vec2 oldWorldPosition = GetWorldPosition();

		if (m_pParent != nullptr)
		{
			m_pParent->RemoveChild(this);
		}

		m_pParent = pParent;
		m_pTransform->SetDirty();

		if (m_pParent != nullptr)
		{
			m_pParent->AddChild(this);
		}

		if (keepWorldPosition)
		{
			glm::vec2 offset = oldWorldPosition - GetWorldPosition();
			SetPosition(GetLocalPosition() + offset);
		}
	}

	void Actor::ForEachChild(const std::function<void(Actor&)>& functor) const
	{
		std::ranges::for_each(m_Children, [&functor](auto& pChild) { functor(*pChild); });
	}

	bool Actor::HasParent() const
	{
		return m_pParent != nullptr;
	}

	Actor* Actor::GetParent() const
	{
		return m_pParent;
	}

	void Actor::Destroy()
	{
		m_Scene.RemoveActor(this);
	}

	Scene& Actor::GetScene() const
	{
		return m_Scene;
	}

	void Actor::SetEnabled(bool enabled)
	{
		m_IsEnabled = enabled;
	}

	bool Actor::IsEnabled() const
	{
		return m_IsEnabled;
	}

	void Actor::AddChild(Actor* pChild)
	{
		HyperAssert(&pChild->GetScene() == &m_Scene, "pChild doesn't belong in the same scene");
		m_Children.emplace_back(pChild);
	}

	void Actor::RemoveChild(Actor* pChild)
	{
		HyperAssert(&pChild->GetScene() == &m_Scene, "pChild doesn't belong in the same scene");
		m_Children.erase(std::remove(m_Children.begin(), m_Children.end(), pChild));
	}
}
