#include "hyper/graphics/context.h"
#include "hyper/scene/components/rect_component.h"
#include "hyper/scene/actor.h"

namespace hyper
{
	RectComponent::RectComponent(Actor& actor, float width, float height, const glm::vec4& color)
		: AComponent(actor)
		, m_Width{ width }
		, m_Height{ height }
		, m_Color{ color }
	{

	}

	void RectComponent::SetSize(float width, float height)
	{
		m_Width = width;
		m_Height = height;
	}

	void RectComponent::SetColor(const glm::vec4& color)
	{
		m_Color = color;
	}

	void RectComponent::OnUpdate(float)
	{
		
	}

	void RectComponent::OnRender(const IContext& context) const
	{
		float halfWidth = m_Width * 0.5f;
		float halfHeight = m_Height * 0.5f;

		const glm::vec2& position = GetActor().GetWorldPosition();

		Rectf rect = {
			.x = position.x - halfWidth,
			.y = position.y - halfHeight,
			.width = m_Width,
			.height = m_Height
		};

		context.DrawRect(rect, m_Color);
	}
}
