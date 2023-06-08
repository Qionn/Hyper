#include "pause_command.h"

namespace burger_time
{
	PauseCommand::PauseCommand(MenuFSMComponent* pMenuFSM)
		: m_pMenuFSM{ pMenuFSM }
	{
		m_pState = m_pMenuFSM->CreateState<PauseMenuState>();
	}

	void PauseCommand::Execute()
	{
		m_pMenuFSM->PushMenuState(m_pState);
	}
}
