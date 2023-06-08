#ifndef __BURGER_TIME_MENU_COMMAND_H__
#define __BURGER_TIME_MENU_COMMAND_H__

#include <hyper/service/sound_service.h>
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

		hyper::SoundId m_CursorSoundId;
		hyper::SoundId m_SelectSoundId;
	};
}

#endif // !__BURGER_TIME_MENU_COMMAND_H__
