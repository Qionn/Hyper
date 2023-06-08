#include "constants.h"
#include "level_menu_state.h"

#include "components/menu_fsm_component.h"
#include "scenes/level_scene.h"

#include <hyper/scene/scene.h>

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
		LoadLevel("assets/maps/level_01.map");
	}

	void LevelMenuState::OnLevel2Select()
	{
		LoadLevel("assets/maps/level_02.map");
	}

	void LevelMenuState::OnLevel3Select()
	{
		LoadLevel("assets/maps/level_03.map");
	}

	void LevelMenuState::LoadLevel(std::string_view mapFile)
	{
		using namespace std::placeholders;
		Scene& scene = GetMenuFSM()->GetScene();
		scene.RequestLoad(std::bind(&LoadLevelScene, _1, _2, mapFile));
	}
}
