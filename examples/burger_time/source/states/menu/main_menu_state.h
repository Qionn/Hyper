#ifndef __BURGER_TIME_MAIN_MENU_STATE_H__
#define __BURGER_TIME_MAIN_MENU_STATE_H__

#include <vector>

#include <hyper/service/sound_service.h>
#include <hyper/fwd.h>

#include "states/menu_state.h"

namespace burger_time
{
	class MainMenuState final : public IMenuState
	{
	public:
		MainMenuState(hyper::Scene& scene);

		void OnEnter() override;
		void OnExit() override;
		void PerformAction(Action action) override;

		MainMenuState(const MainMenuState&)				= delete;
		MainMenuState(MainMenuState&&)					= delete;
		MainMenuState& operator=(const MainMenuState&)	= delete;
		MainMenuState& operator=(MainMenuState&&)		= delete;

		~MainMenuState() = default;

	private:
		hyper::Actor* m_pRootActor;

		uint32_t m_CurrentItem = 0;
		std::vector<hyper::Actor*> m_Items;
		hyper::Actor* m_pItemMarkerLeft;
		hyper::Actor* m_pItemMarkerRight;

		hyper::SoundId m_NavigateSoundId;

	private:
		void SetupTitleActors(hyper::Scene& scene);
		void SetupItemActors(hyper::Scene& scene);
		void SetupItemMarkers(hyper::Scene& scene);

		void SelectItem(uint32_t item);
	};
}

#endif // !__BURGER_TIME_MAIN_MENU_STATE_H__
