#ifndef __BURGER_TIME_MENU_STACK_COMPONENT_H__
#define __BURGER_TIME_MENU_STACK_COMPONENT_H__

#include <memory>
#include <stack>

#include <hyper/scene/component.h>

#include "states/menu/main_menu_state.h"
#include "states/menu/options_menu_state.h"
#include "states/menu/play_menu_state.h"

namespace burger_time
{
	class MenuStackComponent final : public hyper::AComponent
	{
	public:
		MenuStackComponent(hyper::Actor& actor);

		void PushMenuState(IMenuState* pState);
		void PopMenuState();

		IMenuState* GetCurrentMenuState() const;

		MainMenuState* GetMainMenuState() const;
		OptionsMenuState* GetOptionsMenuState() const;
		PlayMenuState* GetPlayMenuState() const;

		~MenuStackComponent() = default;

	private:
		std::stack<IMenuState*> m_StateStack;
		std::unique_ptr<MainMenuState> m_pMainMenuState;
		std::unique_ptr<OptionsMenuState> m_pOptionsMenuState;
		std::unique_ptr<PlayMenuState> m_pPlayMenuState;

	private:
		void OnUpdate(float dt) override;
		void OnRender(const hyper::IContext& context) const override;
	};
}

#endif // !__BURGER_TIME_MENU_STACK_COMPONENT_H__
