#ifndef __BURGER_TIME_MAIN_MENU_SCENE_H__
#define __BURGER_TIME_MAIN_MENU_SCENE_H__

#include <hyper/service/service_hub.h>
#include <hyper/utils/command.h>
#include <hyper/fwd.h>

#include "components/menu_fsm_component.h"

namespace burger_time
{
	class MenuActionCommand final : public hyper::ICommand
	{
	public:
		MenuActionCommand(MenuFSMComponent* pMenuFSM, IMenuState::Action action)
			: m_pMenuFSM{ pMenuFSM }, m_Action{ action } {}

		void Execute() override
		{
			m_pMenuFSM->GetCurrentMenuState()->PerformAction(m_Action);
		}

	private:
		MenuFSMComponent* m_pMenuFSM;
		IMenuState::Action m_Action;
	};

	class MenuReturnCommand final : public hyper::ICommand
	{
	public:
		MenuReturnCommand(MenuFSMComponent* pMenuFSM)
			: m_pMenuFSM{ pMenuFSM } {}

		void Execute() override
		{
			m_pMenuFSM->PopMenuState();
		}

	private:
		MenuFSMComponent* m_pMenuFSM;
	};

	void LoadMainMenuScene(hyper::Scene& scene, hyper::Input& input);
}

#endif // !__BURGER_TIME_MAIN_MENU_SCENE_H__
