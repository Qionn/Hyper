#ifndef __BURGER_TIME_AI_COMPONENT_H__
#define __BURGER_TIME_AI_COMPONENT_H__

#include <hyper/scene/component.h>

#include "components/character_component.h"

namespace burger_time
{
	class EnemyComponent final : public hyper::AComponent
	{
	public:
		enum class Type
		{
			eHotdog,
			ePicke,
			eEgg
		};

	public:
		EnemyComponent(hyper::Actor& actor, Type type);

		void SetTargetActor(hyper::Actor* pActor);
		hyper::Actor* GetTargetActor() const;

		std::string_view GetSpritePath() const;

		~EnemyComponent() = default;

	private:
		hyper::Actor* m_pTargetActor = nullptr;
		CharacterComponent* m_pCharacter;
		Type m_Type;

	private:
		void OnUpdate(float dt) override;
		void OnRender(const hyper::IContext& context) const override;

		void UpdateAIBrain();
	};
}

#endif // !__BURGER_TIME_AI_COMPONENT_H__
