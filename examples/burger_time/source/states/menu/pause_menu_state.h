#ifndef __BURGER_TIME_PAUSE_MENU_STATE_H__
#define __BURGER_TIME_PAUSE_MENU_STATE_H__

#include <memory>

#include "states/menu/level_menu_state.h"

namespace burger_time
{
	class MenuFSMComponent;

	class PauseMenuState final : public AMenuState
	{
	public:
		PauseMenuState(MenuFSMComponent* pMenuFSM, hyper::Input& input);
		~PauseMenuState() = default;

	private:
		void OnResumeSelect(hyper::Input& input);
		void OnMuteSelect();
		void OnSkipLevelSelect();
		void OnExitSelect();

		void SetupBackground();
	};
}

#endif // !__BURGER_TIME_PAUSE_MENU_STATE_H__
