#ifndef __BURGER_TIME_END_MENU_STATE_H__
#define __BURGER_TIME_END_MENU_STATE_H__

#include "gamemodes/solo_gamemode.h"
#include "states/menu/level_menu_state.h"

namespace burger_time
{
	class EndMenuState final : public AMenuState
	{
	public:
		EndMenuState(MenuFSMComponent* pMenuFSM);
		~EndMenuState() = default;

	private:
		void OnContinueSelect();
	};
}

#endif // !__BURGER_TIME_END_MENU_STATE_H__
