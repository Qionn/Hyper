#ifndef __BURGER_TIME_CHARACTER_COMPONENT_H__
#define __BURGER_TIME_CHARACTER_COMPONENT_H__

#include <hyper/scene/component.h>

#include "components/map_component.h"

namespace burger_time
{
	class CharacterComponent final : public hyper::AComponent
	{
	public:
		using Platform = MapComponent::Platform;
		using Ladder = MapComponent::Ladder;

	public:
		CharacterComponent(hyper::Actor& actor, const MapComponent* pMap, float speed, float height);

		void Move(const glm::vec2& direction);

		bool IsOnPlatform() const;
		bool IsOnLadder() const;

		glm::vec2 GetFeetPosition() const;

		~CharacterComponent() = default;

	private:
		const MapComponent* m_pMap;
		const Platform* m_pPlatform = nullptr;
		const Ladder* m_pLadder = nullptr;

		float m_Speed;
		float m_Height = 0.0f;
		float m_Deltatime = 0.0f;

	private:
		void ClampPositionToPlatform(const Platform& platform);
		void ClampPositionToLadder(const Ladder& ladder);

		void OnUpdate(float dt) override;
		void OnRender(const hyper::IContext& context) const override;
	};
}

#endif // !__BURGER_TIME_CHARACTER_COMPONENT_H__
