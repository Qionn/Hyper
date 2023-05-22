#include "hyper/graphics/context.h"
#include "hyper/scene/components/sprite_component.h"
#include "hyper/scene/actor.h"

namespace hyper
{
	SpriteComponent::SpriteComponent(Actor* pActor, std::string_view filepath)
		: AComponent(pActor)
	{
		m_pTexture = GetSceneContext().CreateTexture(filepath);
		m_Width		= static_cast<float>(m_pTexture->GetWidth());
		m_Height	= static_cast<float>(m_pTexture->GetHeight());
	}

	void SpriteComponent::SetSize(float width, float height)
	{
		m_Width = width;
		m_Height = height;
	}

	void SpriteComponent::OnUpdate()
	{

	}

	void SpriteComponent::OnRender() const
	{
		GetSceneContext().DrawTexture(*m_pTexture, GetActor()->GetWorldPosition(), m_Width, m_Height);
	}
}
