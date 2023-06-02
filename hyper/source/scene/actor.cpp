#include "hyper/scene/components/transform_component.h"
#include "hyper/scene/actor.h"
#include "hyper/scene/scene.h"
#include "hyper/utils/assert.h"

#include <algorithm>

namespace hyper
{
	Actor::Actor(Scene& scene)
		: m_pScene{ &scene }
	{
		m_pTransform = AddComponent<TransformComponent>();
	}

	Actor::~Actor()
	{
		if (m_pParent != nullptr)
		{
			m_pParent->RemoveChild(this);
		}
	}

	void Actor::Update(float dt)
	{
		for (auto& [id, pComponent] : m_Components)
		{
			pComponent->OnUpdate(dt);
		}

		for (auto& pChild : m_Children)
		{
			pChild->Update(dt);
		}
	}

	void Actor::Render(const IContext& context) const
	{
		for (const auto& [id, pComponent] : m_Components)
		{
			pComponent->OnRender(context);
		}

		for (const auto& pChild : m_Children)
		{
			pChild->Render(context);
		}
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

	void Actor::ForEachChild(const std::function<void(Actor&)>& functor) const
	{
		std::ranges::for_each(m_Children, [&functor](auto& pChild) {
			functor(*pChild);
		});
	}

	bool Actor::HasParent() const
	{
		return m_pParent != nullptr;
	}

	void Actor::SetParent(Actor* pParent, bool keepWorldPosition)
	{
		glm::vec2 oldWorldPosition;
		if (keepWorldPosition)
		{
			oldWorldPosition = GetWorldPosition();
		}

		if (m_pParent != nullptr)
		{
			m_pParent->RemoveChild(this);
		}

		m_pParent = pParent;
		m_pTransform->SetDirty();

		if (m_pParent != nullptr)
		{
			m_pParent->AddChild(shared_from_this());
		}

		if (keepWorldPosition)
		{
			glm::vec2 offset = oldWorldPosition - GetWorldPosition();
			SetPosition(GetLocalPosition() + offset);
		}
	}

	Actor* Actor::GetParent() const
	{
		return m_pParent;
	}

	Scene* Actor::GetScene() const
	{
		return m_pScene;
	}

	void Actor::AddChild(std::shared_ptr<Actor> pChild)
	{
		HyperAssert(pChild->GetScene() == m_pScene, "pChild doesn't belong in the same scene");
		m_Children.emplace_back(pChild);
	}

	void Actor::RemoveChild(Actor* pChild)
	{
		HyperAssert(pChild->GetScene() == m_pScene, "pChild doesn't belong in the same scene");

		auto pred = [pChild](auto& pC) { return pC.get() == pChild; };
		m_Children.erase(std::remove_if(m_Children.begin(), m_Children.end(), pred), m_Children.end());
	}
}
