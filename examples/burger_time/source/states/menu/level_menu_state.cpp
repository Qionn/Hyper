#include "constants.h"
#include "level_menu_state.h"

#include "components/menu_fsm_component.h"

using namespace hyper;

namespace burger_time
{
	LevelMenuState::LevelMenuState(MenuFSMComponent* pMenuFSM)
		: AMenuState(pMenuFSM, 32, 80.0f)
	{
		AddItem("Level 1", std::bind(&LevelMenuState::OnLevel1Select, this));
		AddItem("Level 2", std::bind(&LevelMenuState::OnLevel2Select, this));
		AddItem("Level 3", std::bind(&LevelMenuState::OnLevel3Select, this));
	}

	void LevelMenuState::OnEnter()
	{
		AMenuState::OnEnter();
		SetCursor(0);
	}

	void LevelMenuState::OnLevel1Select()
	{

	}

	void LevelMenuState::OnLevel2Select()
	{

	}

	void LevelMenuState::OnLevel3Select()
	{

	}
}
