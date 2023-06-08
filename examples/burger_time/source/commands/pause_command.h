#ifndef __BURGER_TIME_PAUSE_COMMAND_H__
#define __BURGER_TIME_PAUSE_COMMAND_H__

#include <hyper/service/sound_service.h>
#include <hyper/utils/command.h>

#include "components/menu_fsm_component.h"
#include "states/menu/pause_menu_state.h"

namespace burger_time
{
	class PauseCommand final : public hyper::ICommand
	{
	public:
		PauseCommand(MenuFSMComponent* pMenuFSM);
		void Execute() override;

	private:
		MenuFSMComponent* m_pMenuFSM;
		PauseMenuState* m_pState;
	};
}

#endif // !__BURGER_TIME_PAUSE_COMMAND_H__
