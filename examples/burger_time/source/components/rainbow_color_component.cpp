#include "rainbow_color_component.h"

#include <hyper/scene/components/text_component.h>
#include <hyper/scene/actor.h>

#include <cmath>

using namespace hyper;

namespace burger_time
{
	RainbowColorComponent::RainbowColorComponent(Actor& actor, float speed)
		: AComponent(actor)
		, m_Speed{ speed }
	{

	}

	void RainbowColorComponent::OnUpdate(float dt)
	{
		m_Degrees += m_Speed * dt;
		if (m_Degrees > 360.0f)
		{
			m_Degrees -= 360.0f;
		}

		TextComponent* pText = GetActor().GetComponent<TextComponent>();
		if (pText != nullptr)
		{
			pText->SetColor(ToRGB(m_Degrees, .7f, 1.0f));
		}
	}

	void RainbowColorComponent::OnRender(const IContext&) const
	{

	}

	/* static */ glm::vec3 RainbowColorComponent::ToRGB(float h, float s, float v)
	{
		if (s == 0)
		{
			return glm::vec3(v);
		}

		h /= 60;

		int sector = static_cast<int>(std::floor(h));
		float sectorPos = h - sector;

		float p = v * (1 - s);
		float q = v * (1 - s * sectorPos);
		float t = v * (1 - s * (1 - sectorPos));

		switch (sector)
		{
			case 0:		return glm::vec3(v, t, p);
			case 1:		return glm::vec3(q, v, p);
			case 2:		return glm::vec3(p, v, t);
			case 3:		return glm::vec3(p, q, v);
			case 4:		return glm::vec3(t, p, v);
			default:	return glm::vec3(v, p, q);
		}
	}

}
