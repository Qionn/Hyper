#include "hyper/graphics/context.h"
#include "hyper/scene/components/sprite_component.h"
#include "hyper/scene/actor.h"
#include "hyper/scene/scene.h"

namespace hyper
{
	SpriteComponent::SpriteComponent(Actor* pActor, std::string_view filepath)
		: AComponent(pActor)
	{
		IContext& context = GetScene()->GetContext();

		m_pTexture			= context.CreateTexture(filepath);

		m_ClipRect.x		= 0;
		m_ClipRect.y		= 0;
		m_ClipRect.width	= m_pTexture->GetWidth();
		m_ClipRect.height	= m_pTexture->GetHeight();
	}

	void SpriteComponent::SetScale(float scale)
	{
		m_Scale = scale;
	}
	
	void SpriteComponent::SetClipRect(const Recti& rect)
	{
		m_ClipRect = rect;
	}

	void SpriteComponent::OnUpdate(float)
	{

	}

	void SpriteComponent::OnRender(const IContext& context) const
	{
		float width = m_ClipRect.width * m_Scale;
		float height = m_ClipRect.height * m_Scale;

		glm::vec2 worldPos = GetActor()->GetWorldPosition();

		Rectf dstRect = {
			.x			= worldPos.x - (width * 0.5f),
			.y			= worldPos.y - (height * 0.5f),
			.width		= width,
			.height		= height
		};

		context.DrawTexture(*m_pTexture, m_ClipRect, dstRect);
	}
}
