#include "end_menu_state.h"

#include "components/menu_fsm_component.h"
#include "scenes/main_menu_scene.h"

#include <hyper/scene/scene.h>

using namespace hyper;

namespace burger_time
{
	EndMenuState::EndMenuState(MenuFSMComponent* pMenuFSM)
		: AMenuState(pMenuFSM, 46, 60.0f)
	{
		AddItem("Continue", std::bind(&EndMenuState::OnContinueSelect, this));
	}

	void EndMenuState::OnContinueSelect()
	{
		using namespace std::placeholders;
		Scene& scene = GetMenuFSM()->GetScene();
		scene.RequestLoad(std::bind(&LoadMainMenuScene, _1, _2));
	}
}
