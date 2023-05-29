#include "hyper/scene/components/transform_component.h"
#include "hyper/scene/actor.h"

namespace hyper
{
	TransformComponent::TransformComponent(Actor* pActor)
		: AComponent(pActor)
	{

	}

	void TransformComponent::SetPosition(float x, float y)
	{
		m_Position = { x, y };
		SetDirty();
	}

	void TransformComponent::SetPosition(const glm::vec2& position)
	{
		SetPosition(position.x, position.y);
	}

	const glm::vec2& TransformComponent::GetLocalPosition() const
	{
		return m_Position;
	}

	const glm::vec2& TransformComponent::GetWorldPosition()
	{
		if (m_IsDirty)
		{
			m_WorldPosition = m_Position;

			if (Actor* pParent = GetActorParent(); pParent != nullptr)
			{
				m_WorldPosition += pParent->GetWorldPosition();
			}
		}

		return m_WorldPosition;
	}

	void TransformComponent::SetDirty()
	{
		m_IsDirty = true;

		GetActor()->ForEachChild([](Actor& actor) {
			actor.GetComponent<TransformComponent>()->SetDirty();
		});
	}

	void TransformComponent::OnUpdate(float)
	{

	}

	void TransformComponent::OnRender(const IContext&) const
	{

	}

}
