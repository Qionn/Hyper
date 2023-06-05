#ifndef __BURGER_TIME_MENU_FSM_COMPONENT_H__
#define __BURGER_TIME_MENU_FSM_COMPONENT_H__

#include <memory>
#include <stack>

#include <hyper/scene/component.h>
#include <hyper/service/sound_service.h>

#include "states/menu/main_menu_state.h"

namespace burger_time
{
	class MenuFSMComponent final : public hyper::AComponent
	{
	public:
		MenuFSMComponent(hyper::Actor& actor);

		void PushMenuState(IMenuState* pState);
		void PopMenuState();

		IMenuState* GetCurrentMenuState() const;

		~MenuFSMComponent() = default;

	private:
		std::stack<IMenuState*> m_Stack;
		std::unique_ptr<MainMenuState> m_pDefaultState;

		hyper::SoundId m_SoundId;

	private:
		void OnUpdate(float dt) override;
		void OnRender(const hyper::IContext& context) const override;
	};
}

#endif // !__BURGER_TIME_MENU_FSM_COMPONENT_H__
