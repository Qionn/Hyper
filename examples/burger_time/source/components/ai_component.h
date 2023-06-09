#ifndef __BURGER_TIME_AI_COMPONENT_H__
#define __BURGER_TIME_AI_COMPONENT_H__

#include <hyper/scene/component.h>

#include "components/character_component.h"

namespace burger_time
{
	class AIComponent final : public hyper::AComponent
	{
	public:
		AIComponent(hyper::Actor& actor, hyper::Actor* pTargetActor);

		void SetTargetActor(hyper::Actor* pActor);
		hyper::Actor* GetTargetActor() const;

		~AIComponent() = default;

	private:
		hyper::Actor* m_pTargetActor;
		CharacterComponent* m_pCharacter;

	private:
		void OnUpdate(float dt) override;
		void OnRender(const hyper::IContext& context) const override;
	};
}

#endif // !__BURGER_TIME_AI_COMPONENT_H__
