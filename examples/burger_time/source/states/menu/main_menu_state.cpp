#include "constants.h"
#include "main_menu_state.h"

#include "components/menu_fsm_component.h"

#include <hyper/scene/scene.h>

using namespace hyper;

namespace burger_time
{
	MainMenuState::MainMenuState(MenuFSMComponent* pMenuFSM)
		: AMenuState(pMenuFSM, 32, 80.0f)
	{
		m_pLevelState = std::make_unique<LevelMenuState>(pMenuFSM);

		AddItem("Solo", std::bind(&MainMenuState::OnSoloSelect, this));
		AddItem("Co-op", std::bind(&MainMenuState::OnCoopSelect, this));
		AddItem("Versus", std::bind(&MainMenuState::OnVersusSelect, this));
		AddItem("Exit", std::bind(&MainMenuState::OnExitSelect, this));
	}

	void MainMenuState::OnSoloSelect()
	{
		m_pLevelState->SetGamemode(&m_SoloGamemode);
		GetMenuFSM()->PushMenuState(m_pLevelState.get());
	}

	void MainMenuState::OnCoopSelect()
	{
		m_pLevelState->SetGamemode(&m_CoopGamemode);
		GetMenuFSM()->PushMenuState(m_pLevelState.get());
	}

	void MainMenuState::OnVersusSelect()
	{
		m_pLevelState->SetGamemode(&m_VersusGamemode);
		GetMenuFSM()->PushMenuState(m_pLevelState.get());
	}

	void MainMenuState::OnExitSelect()
	{
		Scene& scene = GetMenuFSM()->GetScene();
		scene.RequestStop();
	}
}
