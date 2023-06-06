#ifndef __BURGER_TIME_LEVEL_MENU_STATE_H__
#define __BURGER_TIME_LEVEL_MENU_STATE_H__

#include <memory>

#include "states/menu_state.h"

namespace burger_time
{
	class MenuFSMComponent;

	class LevelMenuState final : public AMenuState
	{
	public:
		LevelMenuState(MenuFSMComponent* pMenuFSM);
		~LevelMenuState() = default;

		void OnEnter() override;

	private:
		void OnLevel1Select();
		void OnLevel2Select();
		void OnLevel3Select();
	};
}

#endif // !__BURGER_TIME_LEVEL_MENU_STATE_H__
