#ifndef __BURGER_TIME_SCENE_EVENTS_H__
#define __BURGER_TIME_SCENE_EVENTS_H__

#include <hyper/event/event.h>
#include <hyper/fwd.h>

#include "components/ingredient_component.h"

namespace burger_time
{
	class PlayerHitEvent final : public hyper::AEvent
	{
	public:
		hyper::Actor* pPlayer;

	public:
		explicit PlayerHitEvent(hyper::Actor* pPlayer)
			: pPlayer{ pPlayer } {}
	};

	class IngredientDropEvent final : public hyper::AEvent
	{
	public:
		IngredientComponent* pIngredient;

	public:
		explicit IngredientDropEvent(IngredientComponent* pIngredient)
			: pIngredient{ pIngredient } {}
	};

	class IngredientSliceEvent final : public hyper::AEvent
	{
	public:
		IngredientComponent* pIngredient;

	public:
		explicit IngredientSliceEvent(IngredientComponent* pIngredient)
			: pIngredient{ pIngredient } {}
	};

	class BurgerCompleteEvent final : public hyper::AEvent
	{
	public:
		BurgerCompleteEvent() = default;
	};

	class LevelCompleteEvent final : public hyper::AEvent
	{
	public:
		LevelCompleteEvent() = default;
	};
}

#endif //!__BURGER_TIME_SCENE_EVENTS_H__
