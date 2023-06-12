#include "hyper/scene/components/collider_component.h"
#include "hyper/scene/scene.h"
#include "hyper/utils/rect.h"

namespace hyper
{
	ColliderComponent::ColliderComponent(Actor& actor, float width, float height, float yOffset)
		: AComponent(actor)
		, m_Width{ width }
		, m_Height{ height }
		, m_HalfWidth{ width * 0.5f }
		, m_HalfHeight{ height * 0.5f }
		, m_OffsetY{ yOffset }
	{
		GetScene().GetPhysicsWorld().AddCollider(this);
	}

	ColliderComponent::~ColliderComponent()
	{
		GetScene().GetPhysicsWorld().RemoveCollider(this);
	}

	void ColliderComponent::SetSize(float width, float height)
	{
		m_Width			= width;
		m_Height		= height;
		m_HalfWidth		= width * 0.5f;
		m_HalfHeight	= height * 0.5f;
	}

	bool ColliderComponent::IsOverlapping(const ColliderComponent& other) const
	{
		// https://stackoverflow.com/a/306379

		const glm::vec2& posA = GetActor().GetWorldPosition();
		Rectf a{ posA.x - m_HalfWidth, posA.y - m_HalfHeight - m_OffsetY, m_Width, m_Height };

		const glm::vec2& posB = other.GetActor().GetWorldPosition();
		Rectf b{ posB.x - other.m_HalfWidth, posB.y - other.m_HalfHeight - other.m_OffsetY, other.m_Width, other.m_Height };

		bool overlapX = (ValueInRange(a.x, b.x, b.x + b.width) ||
						 ValueInRange(b.x, a.x, a.x + a.width));

		bool overlapY = (ValueInRange(a.y, b.y, b.y + b.height) ||
						 ValueInRange(b.y, a.y, a.y + a.height));

		return overlapX && overlapY;
	}

	void ColliderComponent::OnUpdate(float)
	{

	}

	void ColliderComponent::OnRender(const IContext&) const
	{

	}

	/* static */ bool ColliderComponent::ValueInRange(float value, float min, float max)
	{
		return (value >= min) && (value <= max);
	}
}
