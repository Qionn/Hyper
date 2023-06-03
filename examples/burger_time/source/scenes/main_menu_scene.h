#ifndef __BURGER_TIME_MAIN_MENU_SCENE_H__
#define __BURGER_TIME_MAIN_MENU_SCENE_H__

#include <hyper/utils/command.h>
#include <hyper/fwd.h>

#include "components/menu_stack_component.h"

namespace burger_time
{
	class ChangeMenuCommand final : public hyper::ICommand
	{
	public:
		ChangeMenuCommand(MenuStackComponent& menuStack, IMenuState* pState)
			:m_MenuStack{ menuStack }, m_pState{ pState } {}

		void Execute() override
		{
			if (m_pState != nullptr)
			{
				m_MenuStack.PushMenuState(m_pState);
			}
			else
			{
				m_MenuStack.PopMenuState();
			}
		}

	private:
		MenuStackComponent& m_MenuStack;
		IMenuState* m_pState;
	};

	void LoadMainMenuScene(hyper::Scene& scene, hyper::Input& input);
}

#endif // !__BURGER_TIME_MAIN_MENU_SCENE_H__
