#include "menu_command.h"

#include <hyper/service/service_hub.h>

using namespace hyper;

namespace burger_time
{
	MenuCommand::MenuCommand(MenuFSMComponent* pMenuFSM, Action action)
		: m_pMenuFSM{ pMenuFSM }
		, m_Action{ action }
	{
		ISoundService* pSoundService = ServiceHub::SoundService();
		m_CursorSoundId = pSoundService->AddSound("assets/audio/menu_navigate_01.wav");
		m_SelectSoundId = pSoundService->AddSound("assets/audio/menu_navigate_02.wav");
	}

	void MenuCommand::Execute()
	{
		ISoundService* pSoundService = ServiceHub::SoundService();
		AMenuState* pState = m_pMenuFSM->GetCurrentMenuState();

		switch (m_Action)
		{
			case Action::eCursorUp:
				pSoundService->Play(m_CursorSoundId, 0.5f);
				pState->MoveCursor(1);
				break;

			case Action::eCursorDown:
				pSoundService->Play(m_CursorSoundId, 0.5f);
				pState->MoveCursor(-1);
				break;

			case Action::eSelect:
				pSoundService->Play(m_SelectSoundId, 0.5f);
				pState->Select();
				break;

			case Action::eReturn:
				pSoundService->Play(m_SelectSoundId, 0.5f);
				m_pMenuFSM->PopMenuState();
				break;
		}
	}
}
