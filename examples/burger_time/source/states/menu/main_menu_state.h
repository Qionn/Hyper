#ifndef __BURGER_TIME_MAIN_MENU_STATE_H__
#define __BURGER_TIME_MAIN_MENU_STATE_H__

#include <memory>

#include "gamemodes/solo_gamemode.h"
#include "states/menu/level_menu_state.h"

namespace burger_time
{
	class MainMenuState final : public AMenuState
	{
	public:
		MainMenuState(MenuFSMComponent* pMenuFSM);
		~MainMenuState() = default;

	private:
		std::unique_ptr<LevelMenuState> m_pLevelState;

		SoloGamemode m_SoloGamemode;

	private:
		void OnSoloSelect();
		void OnCoopSelect();
		void OnVersusSelect();
		void OnExitSelect();
	};
}

#endif // !__BURGER_TIME_MAIN_MENU_STATE_H__
