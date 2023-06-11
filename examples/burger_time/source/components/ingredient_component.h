#ifndef __BURGER_TIME_INGREDIENT_COMPONENT_H__
#define __BURGER_TIME_INGREDIENT_COMPONENT_H__

#include <array>

#include <hyper/event/physics_events.h>
#include <hyper/event/observer.h>
#include <hyper/scene/component.h>
#include <hyper/fwd.h>

#include "components/map_component.h"

namespace burger_time
{
	enum class IngredientType
	{
		eBunTop,
		eBunBottom,
		eCheese,
		ePatty,
		eTomato,
		eLetuce
	};

	class IngredientComponent final : public hyper::AComponent, public hyper::IObserver
	{
	public:
		using Platform = MapComponent::Platform;
		using Catcher = MapComponent::Catcher;

	public:
		IngredientComponent(hyper::Actor& actor, IngredientType type, MapComponent* pMap);

		void Drop();

		bool IsOnPlatform() const;
		bool IsInCatcher() const;

		~IngredientComponent();

	private:
		const MapComponent* m_pMap;
		const Platform* m_pPlatform = nullptr;

		IngredientType m_Type;

		const float m_Speed = 100.0f;
		bool m_IsInCatcher = false;

		std::array<hyper::Actor*, 4> m_Slices;
		std::array<bool, 4> m_SliceFlags;

	private:
		void SpawnSlices();
		void ClampPositionToPlatform(const Platform& platform);
		void ClampPositionToCatcher(const Catcher& catcher);

		std::string_view GetSpritePath() const;

		void OnUpdate(float dt) override;
		void OnRender(const hyper::IContext& context) const override;

		bool OnEvent(const hyper::AEvent& event) override;
		bool HandleSliceCollision(const hyper::OverlapBeginEvent& event);
		bool HandleIngredientCollision(const hyper::OverlapBeginEvent& event);
	};
}

#endif // !__BURGER_TIME_INGREDIENT_COMPONENT_H__
