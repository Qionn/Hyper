#ifndef __BURGER_TIME_PAUSE_COMMAND_H__
#define __BURGER_TIME_PAUSE_COMMAND_H__

#include <memory>

#include <hyper/input/command_layer.h>
#include <hyper/fwd.h>

#include "components/menu_fsm_component.h"
#include "states/menu/pause_menu_state.h"

namespace burger_time
{
	class PauseCommand final : public hyper::ICommand
	{
	public:
		PauseCommand(MenuFSMComponent* pMenuFSM, hyper::Input& input);
		void Execute() override;

	private:
		MenuFSMComponent* m_pMenuFSM;
		PauseMenuState* m_pState;
		hyper::CommandLayer m_CommandLayer;
		hyper::Input& m_Input;
	};
}

#endif // !__BURGER_TIME_PAUSE_COMMAND_H__
