#ifndef __BURGER_TIME_LEVEL_MENU_STATE_H__
#define __BURGER_TIME_LEVEL_MENU_STATE_H__

#include <memory>
#include <string_view>

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

		void LoadLevel(std::string_view mapFile);
	};
}

#endif // !__BURGER_TIME_LEVEL_MENU_STATE_H__
