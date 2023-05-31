#include "hyper/scene/components/text_component.h"

#include "hyper/graphics/context.h"
#include "hyper/scene/scene.h"

namespace hyper
{
	TextComponent::TextComponent(Actor* pActor, std::string fontPath, int ptSize)
		: AComponent(pActor)
		, m_FontPath{ fontPath }
		, m_PointSize{ ptSize }
		, m_Color{ 0.0f }
	{

	}

	void TextComponent::SetText(std::string_view text, const glm::vec3& color)
	{
		m_Text		= text;
		m_Color		= color;
		m_IsDirty	= true;
	}

	const std::string& TextComponent::GetText() const
	{
		return m_Text;
	}

	const glm::vec3& TextComponent::GetColor() const
	{
		return m_Color;
	}

	int TextComponent::GetPointSize() const
	{
		return m_PointSize;
	}

	void TextComponent::OnUpdate(float)
	{
		if (m_IsDirty)
		{
			IContext& context = GetScene()->GetContext();
			m_pTexture = context.CreateTexture(m_FontPath, m_PointSize, m_Text, m_Color);
			m_IsDirty = false;
		}
	}

	void TextComponent::OnRender(const IContext& context) const
	{
		if (m_pTexture != nullptr)
		{
			glm::vec2 worldPos = GetActor()->GetWorldPosition();

			Rectf dstRect = {
				.x			= worldPos.x,
				.y			= worldPos.y,
				.width		= static_cast<float>(m_pTexture->GetWidth()),
				.height		= static_cast<float>(m_pTexture->GetHeight())
			};

			context.DrawTexture(*m_pTexture, dstRect);
		}
	}
}
