#ifndef __BURGER_TIME_MAIN_MENU_STATE_H__
#define __BURGER_TIME_MAIN_MENU_STATE_H__

#include <memory>

#include "states/menu/level_menu_state.h"

namespace burger_time
{
	class MenuFSMComponent;

	class MainMenuState final : public AMenuState
	{
	public:
		MainMenuState(MenuFSMComponent* pMenuFSM);
		~MainMenuState() = default;

	private:
		std::unique_ptr<LevelMenuState> m_pLevelState;

	private:
		void OnSoloSelect();
		void OnCoopSelect();
		void OnVersusSelect();
		void OnExitSelect();
	};
}

#endif // !__BURGER_TIME_MAIN_MENU_STATE_H__
