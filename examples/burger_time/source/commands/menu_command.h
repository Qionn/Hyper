#ifndef __BURGER_TIME_MENU_COMMAND_H__
#define __BURGER_TIME_MENU_COMMAND_H__

#include <hyper/utils/command.h>

#include "components/menu_fsm_component.h"

namespace burger_time
{
	class MenuCommand final : public hyper::ICommand
	{
	public:
		enum class Action
		{
			eCursorUp,
			eCursorDown,
			eSelect,
			eReturn
		};

	public:
		MenuCommand(MenuFSMComponent* pMenuFSM, Action action);
		void Execute() override;

	private:
		MenuFSMComponent* m_pMenuFSM;
		Action m_Action;
	};
}

#endif // !__BURGER_TIME_MENU_COMMAND_H__
