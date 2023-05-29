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

	void Actor::Update(float dt)
	{
		for (auto& [id, pComponent] : m_Components)
		{
			pComponent->OnUpdate(dt);
		}

		for (Actor* pChild : m_Children)
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

		for (const Actor* pChild : m_Children)
		{
			pChild->Render(context);
		}
	}

	Scene* Actor::GetScene() const
	{
		return m_pScene;
	}

	void Actor::SetParent(Actor* pParent, bool keepWorldPosition)
	{
		glm::vec2 currentWorldPosition = GetWorldPosition();

		if (m_pParent != nullptr)
		{
			m_pParent->RemoveChild(this);
		}

		m_pParent = pParent;

		if (m_pParent != nullptr)
		{
			m_pParent->AddChild(this);
			m_pTransform->SetDirty();

			if (keepWorldPosition)
			{
				glm::vec2 newPosition = currentWorldPosition - GetWorldPosition();
				SetPosition(newPosition);
			}
		}
		else if (keepWorldPosition)
		{
			SetPosition(currentWorldPosition);
		}
	}

	Actor* Actor::GetParent() const
	{
		return m_pParent;
	}

	void Actor::ForEachChild(const std::function<void(Actor&)>& functor)
	{
		std::ranges::for_each(m_Children, [&functor](Actor* pChild){
			functor(*pChild);
		});
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

	void Actor::AddChild(Actor* pChild)
	{
		m_Children.emplace_back(pChild);
	}

	void Actor::RemoveChild(const Actor* pChild)
	{
		auto it = std::ranges::find(m_Children, pChild);
		if (it != m_Children.end())
		{
			m_Children.erase(it);
		}
	}
}
