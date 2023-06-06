#include "menu_command.h"

namespace burger_time
{
	MenuCommand::MenuCommand(MenuFSMComponent* pMenuFSM, Action action)
		: m_pMenuFSM{ pMenuFSM }
		, m_Action{ action }
	{

	}

	void MenuCommand::Execute()
	{
		AMenuState* pState = m_pMenuFSM->GetCurrentMenuState();

		switch (m_Action)
		{
			case Action::eCursorUp:
				pState->MoveCursor(1);
				break;

			case Action::eCursorDown:
				pState->MoveCursor(-1);
				break;

			case Action::eSelect:
				pState->Select();
				break;

			case Action::eReturn:
				m_pMenuFSM->PopMenuState();
				break;
		}
	}
}
