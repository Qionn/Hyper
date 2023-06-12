#ifndef __BURGER_TIME_HUD_COMPONENT_H__
#define __BURGER_TIME_HUD_COMPONENT_H__

#include <vector>

#include <hyper/event/observer.h>
#include <hyper/scene/component.h>
#include <hyper/service/service_hub.h>
#include <hyper/fwd.h>

#include "events/scene_events.h"

namespace burger_time
{
	class HUDComponent final : public hyper::AComponent, public hyper::IObserver
	{
	public:
		HUDComponent(hyper::Actor& actor, int numLives, int numBurgers);

		int GetRemainingLives() const;

		~HUDComponent() = default;

	private:
		std::vector<hyper::Actor*> m_LiveActors;
		hyper::Actor* m_pScoreActor;

		int m_Score = 0;
		int m_NumBurgers;

		hyper::SoundId m_PlayerHitSoundId;
		hyper::SoundId m_IngredientDropSoundId;
		hyper::SoundId m_IngredientSliceSoundId;

	private:
		void OnUpdate(float dt) override;
		void OnRender(const hyper::IContext& context) const override;

		bool OnEvent(const hyper::AEvent& event) override;
		bool OnPlayerHitEvent(const PlayerHitEvent& event);
		bool OnIngredientDropEvent(const IngredientDropEvent& event);
		bool OnIngredientSliceEvent(const IngredientSliceEvent& event);
		bool OnBurgerCompleteEvent(const BurgerCompleteEvent& event);

		void CreateLives(int numLives);
		void CreateScore();
		void UpdateScore();

		void EndLevel(bool playerDied) const;
	};
}

#endif // !__BURGER_TIME_HUD_COMPONENT_H__
