#ifndef __BURGER_TIME_PLAY_MENU_STATE_H__
#define __BURGER_TIME_PLAY_MENU_STATE_H__

#include <memory>

#include <hyper/fwd.h>

#include "states/menu/level_menu_state.h"
#include "utils/menu_item_list.h"

namespace burger_time
{
	class MenuFSMComponent;

	class PlayMenuState final : public IMenuState
	{
	public:
		PlayMenuState(hyper::Scene& scene, MenuFSMComponent* pMenuFSM);

		void OnEnter() override;
		void OnExit() override;
		void PerformAction(Action action) override;

		PlayMenuState(const PlayMenuState&)				= delete;
		PlayMenuState(PlayMenuState&&)					= delete;
		PlayMenuState& operator=(const PlayMenuState&)	= delete;
		PlayMenuState& operator=(PlayMenuState&&)		= delete;

		~PlayMenuState() = default;

	private:
		hyper::Actor* m_pRootActor;

		MenuFSMComponent* m_pMenuFSM;
		std::unique_ptr<LevelMenuState> m_pLevelState;

		std::unique_ptr<MenuItemList> m_pMenuItemList;

	private:
		void SetupTitleActors();
		void SetupMenuItems();

		void OnSoloSelect();
		void OnCoopSelect();
		void OnVersusSelect();
	};
}

#endif // !__BURGER_TIME_PLAY_MENU_STATE_H__
